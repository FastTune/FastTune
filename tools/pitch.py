#!/usr/bin/env python
# -*- coding: utf-8 -*-

import argparse
import os
import math
import audioflux as af
import numpy as np


def make_parser():
    parser = argparse.ArgumentParser()
    parser.add_argument('-i', '--input', type=str,
                        help='Path to input audio file.')
    parser.add_argument('-o', '--output', type=str,
                        help='Path to output txt file, default is the same as input audio file path')
    parser.add_argument('-p', '--pitch', type=str, default='pef',
                      help='select pitch detection algorithm, include pef|ncf|hps|lhs|cep|yin.')
    parser.add_argument('-r', '--samplate', type=int, default=None,
                      help='select samplerate, default is None, which means use the samplerate of the audio file.')
    parser.add_argument('-B', '--bufsize', type=int, default=4096,
                      help='set buffer size, number of frames to run the analysis on, buffer size default=512')
    parser.add_argument('-H', '--hopsize', type=int, default=1024,
                        help='set hopsize, number of frames to read from source before each analysis, hop size default=256')
    parser.add_argument('-R', '--range', type=int, nargs='+',default=[32, 2000],
                        help='select range of low_fre and high_fre, default is low_fre=32, high_fre=2000.')

    return parser

def main():
    parser = make_parser()
    args = parser.parse_args()

    if not args.input:
        raise ValueError('Audio file path must be specified.')
    if not os.path.exists(args.input):
        raise ValueError(f'Audio file does not exist.')

    if not args.output:
        file_path, extension = os.path.splitext(args.input)
        args.output = f"{file_path}.txt"

    low_fre = args.range[0]
    high_fre = args.range[1]
    slide_length = args.hopsize

    bufsize = args.bufsize
    if not ((bufsize & (bufsize - 1)) == 0 and bufsize != 0):
        raise ValueError('bufsize must be a power of 2.')
    radix2_exp = int(math.log(bufsize, 2))

    audio_arr, sr = af.read(args.input, samplate=args.samplate)

    if args.pitch == 'pef':
        pitch_obj = af.PitchPEF(samplate=sr, radix2_exp=radix2_exp, low_fre=low_fre, high_fre=high_fre,
                              window_type=af.type.WindowType.HAMM,
                              cut_fre=4000, slide_length=slide_length, alpha=10, beta=0.5, gamma=1.8)
        fre_arr = pitch_obj.pitch(audio_arr)
    elif args.pitch == 'ncf':
        pitch_obj = af.PitchNCF(samplate=sr, radix2_exp=radix2_exp, low_fre=low_fre, high_fre=high_fre,
                              slide_length=slide_length, window_type=af.type.WindowType.HAMM)
        fre_arr = pitch_obj.pitch(audio_arr)
    elif args.pitch == 'hps':
        pitch_obj = af.PitchHPS(samplate=sr, radix2_exp=radix2_exp, low_fre=low_fre, high_fre=high_fre,
                                slide_length=slide_length, window_type=af.type.WindowType.HAMM,
                                harmonic_count=5)
        fre_arr = pitch_obj.pitch(audio_arr)
    elif args.pitch == 'lhs':
        pitch_obj = af.PitchLHS(samplate=sr, radix2_exp=radix2_exp, low_fre=low_fre, high_fre=high_fre,
                                slide_length=slide_length, window_type=af.type.WindowType.HAMM,
                                harmonic_count=5)
        fre_arr = pitch_obj.pitch(audio_arr)
    elif args.pitch == 'cep':
        pitch_obj = af.PitchCEP(samplate=sr, radix2_exp=radix2_exp, low_fre=low_fre, high_fre=high_fre,
                                slide_length=slide_length, window_type=af.type.WindowType.HAMM)
        fre_arr = pitch_obj.pitch(audio_arr)
    elif args.pitch == 'yin':
        pitch_obj = af.PitchYIN(samplate=sr, radix2_exp=radix2_exp, low_fre=low_fre, high_fre=high_fre,
                                slide_length=slide_length, auto_length=2048)
        fre_arr, _, _ = pitch_obj.pitch(audio_arr)

    hr = af.HarmonicRatio(samplate=sr, low_fre=low_fre, radix2_exp=radix2_exp,
                          window_type=af.type.WindowType.HAMM, slide_length=slide_length)
    ret_arr = hr.harmonic_ratio(audio_arr)
    times = np.arange(fre_arr.shape[-1]) * (pitch_obj.slide_length / sr)

    with open(args.output, 'w') as f:
        f.write("time, fre\n")
        for i,time in enumerate(times):
            ret = ret_arr[i]
            if ret < 0.9:
                continue
            fre = fre_arr[i]
            f.write(str(round(time, 3)) + ',' + str(fre) + '\n')

    print(f'=> Pitch results are successfully saved to {args.output}')



if __name__ == '__main__':
    main()