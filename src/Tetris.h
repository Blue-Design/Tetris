/**
  ******************************************************************************
  * @file    Tetris.h
  * @author  ykaidong (http://www.DevLabs.cn)
  * @version V0.1
  * @date    2014-11-15
  * @brief
  ******************************************************************************
  * Change Logs:
  * Date           Author       Notes
  * 2014-11-15     ykaidong     the first version
  *
  ******************************************************************************
  * @attention
  *
  * Copyright(C) 2013-2014 by ykaidong<ykaidong@126.com>
  *
  * This program is free software; you can redistribute it and/or modify
  * it under the terms of the GNU Lesser General Public License as
  * published by the Free Software Foundation; either version 2 of the
  * License, or (at your option) any later version.
  *
  * This program is distributed in the hope that it will be useful,
  * but WITHOUT ANY WARRANTY; without even the implied warranty of
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  * GNU General Public License for more details.
  *
  * You should have received a copy of the GNU Lesser General Public
  * License along with this program; if not, write to the
  * Free Software Foundation, Inc.,
  * 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _TETRIS_H_
#define _TETRIS_H_

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <stdbool.h>

/* Exported types ------------------------------------------------------------*/

// direction
typedef enum
{
    dire_left,      //!< 左移
    dire_right,     //!< 右移
    dire_down,      //!< 下移
    dire_rotate,    //!< 旋转
} dire_t;

/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
extern bool tetris_move(dire_t direction);
extern void tetris_sync(void);
extern void tetris_sync_all(void);
extern bool tetris_is_game_over(void);

// 初始化, 需要的回调函数说明:
// draw_box_to_map(uint8_t x, uint8_t y, bool box): 当参数为1时在地图上画一个box
//                                                  为0时清除掉box.
// get_random(void): 函数须返回一个随机数, 产生新方块使用
// next_brick_info(uint16_t info): 当产生新方块后回调此函数, 参数为新方块的数据
// remove_line_num(uint8_t line): 当发生消行时回调此函数, 参数为消除的行数
extern void tetris_init(void (*draw_box_to_map)(uint8_t x, uint8_t y, bool box),
                        uint8_t (*get_random)(void),
                        void (*next_brick_info)(uint16_t info),
                        void (*remove_line_num)(uint8_t line));
#endif

/************* Copyright(C) 2013 - 2014 DevLabs **********END OF FILE**********/


