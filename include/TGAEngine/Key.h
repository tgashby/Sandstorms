/**
 * @file Key.h
 *
 * @author Tag Ashby
 * @date 7/2012
 *
 */
#pragma once

#include "ProjIncludes.h"

namespace TGA
{
   /**
    * @enum Key
    *
    * May seem redundant (and it kind of is), but it maps corresponding keys from
    * SDLK_ form to my own form.
    *
    */
	enum Key
	{
		key_A = SDLK_a,
		key_B = SDLK_b,
		key_C = SDLK_c,
		key_D = SDLK_d,
		key_E = SDLK_e,
		key_F = SDLK_f,
		key_G = SDLK_g,
		key_H = SDLK_h,
		key_I = SDLK_i,
		key_J = SDLK_j,
		key_K = SDLK_k,
		key_L = SDLK_l,
		key_M = SDLK_m,
		key_N = SDLK_n,
		key_O = SDLK_o,
		key_P = SDLK_p,
		key_Q = SDLK_q,
		key_R = SDLK_r,
		key_S = SDLK_s,
		key_T = SDLK_t,
		key_U = SDLK_u,
		key_V = SDLK_v,
		key_W = SDLK_w,
		key_X = SDLK_x,
		key_Y = SDLK_y,
		key_Z = SDLK_z,
		key_1 = SDLK_1,
		key_2 = SDLK_2,
		key_3 = SDLK_3,
		key_4 = SDLK_4,
		key_5 = SDLK_5,
		key_6 = SDLK_6,
		key_7 = SDLK_7,
		key_8 = SDLK_8,
		key_9 = SDLK_9,
		key_0 = SDLK_0,
		key_TAB = SDLK_TAB,
		key_SPACE = SDLK_SPACE,
      key_F1 = SDLK_F1,
      key_F2 = SDLK_F2,
      key_F3 = SDLK_F3,
      key_F4 = SDLK_F4,
      key_F5 = SDLK_F5,
      key_F6 = SDLK_F6,
      key_F7 = SDLK_F7,
      key_F8 = SDLK_F8,
      key_F9 = SDLK_F9,
      key_F10 = SDLK_F10,
      key_F11 = SDLK_F11,
      key_F12 = SDLK_F12,
      key_BACKQUOTE = SDLK_BACKQUOTE
	};
}