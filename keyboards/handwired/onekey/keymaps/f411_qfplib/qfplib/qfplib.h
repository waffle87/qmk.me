// Copyright 2015 Mark Owen (qfp@quinapalus.com)
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

extern float qfp_fadd(float x, float y);
extern float qfp_fsub(float x, float y);
extern float qfp_fmul(float x, float y);
extern float qfp_fdiv(float x, float y);
extern float qfp_fdiv_fast(float x, float y);
extern int qfp_float2int(float x);
extern int qfp_float2fix(float x, int y);
extern unsigned int qfp_float2uint(float x);
extern unsigned int qfp_float2ufix(float x, int y);
extern float qfp_int2float(int x);
extern float qfp_fix2float(int x, int y);
extern float qfp_uint2float(unsigned int x);
extern float qfp_ufix2float(unsigned int x, int y);
extern int qfp_fcmp(float x, float y);
extern float qfp_fcos(float x);
extern float qfp_fsin(float x);
extern float qfp_ftan(float x);
extern float qfp_fatan2(float y, float x);
extern float qfp_fexp(float x);
extern float qfp_fln(float x);
extern float qfp_fsqrt(float x);
extern float qfp_fsqrt_fast(float x);
