/**
  ******************************************************************************
  * @file    ui.c
  * @author  ykaidong (http://www.DevLabs.cn)
  * @version V0.3
  * @date    2014-11-15
  * @brief   ����˹���������غ���.
  * @note    ����˹����Ļ���Ԫ����һ����4��С����������ɵĹ���ͼ�Σ�
  *          Ӣ�ĳ�ΪTetromino������ͨ��Ϊ����, �������������Ϊ <b> brick </b> ,
  *          ����7�֣��ֱ���S��Z��L��J��I��O��T��7����ĸ����״��������
  *          ���ǽ�����Tetromino��С�����γ�Ϊ<b> box </b>.
  *
  *          ����Ķ���˹�����ͼ���� 10 * 20 ��box���.
  *          �ڱ�������, �����趨��ͼ��ԭ��λ�����Ͻ�, ����Ϊ(0, 0).
  ******************************************************************************
  * Change Logs:
  * Date           Author       Notes
  * 2014-11-15     ykaidong     the first version
  * 2014-11-23     ykaidong     ����box�ĺ�����������
  * 2014-11-30     ykaidong     ֧�ֲ�ɫ
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

#include "UI.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define     MAP_WIDTH               10      //!< ��ͼ�� 10 ��box
#define     MAP_HEIGHT              20      //!< ��ͼ�� 20 ��box

#define     MAP_START_COLUMN        2
#define     MAP_START_ROW           1

#define     PREVIEW_START_COLUMN    28
#define     PREVIEW_START_ROW       3

#define     UI_COLOR_BASE           8       //!< ��ɫ, �ο�pcc32.h
#define     UI_BG_COLOR             WHITE   //!< ��ͼ����ɫ, �ǿ���̨����

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
 * \brief  �ڴ����ϻ�һ��box, ���Ͻ�����Ϊ(0, 0)
 *
 * \param  x
 * \param  y
 * \param  color ��ɫ, 0 - 7. ע��0��ʾ�����box, ����ɫ
 */
static void draw_box(uint8_t x, uint8_t y, uint8_t color)
{
    gotoTextPos(x, y);

    // ���
    if (!color)
    {
        setTextColor(UI_BG_COLOR);
        printf("��");
    }
    else
    {
#ifdef UI_USE_COLOR
        // ��UI_COLOR_BASE������ɫ
        setTextColor(color + UI_COLOR_BASE);
#else
        // ��ɫģʽ��, ��ǰ��Ϊ��ɫ
        setTextColor(WHITE);
#endif
        printf("��");
    }

    return;
}


/**
 * \brief �ڵ�ͼ����һ��box
 *
 * \param  x ��ͼ��: 0 - 9
 * \param  y ��ͼ��: 0 - 19
 */
void ui_draw_box(uint8_t x, uint8_t y, uint8_t color)
{
    // ����ȫ�ǵ�һ���������ռ�������ַ�λ��
    draw_box(x * 2 + MAP_START_COLUMN, y + MAP_START_ROW, color);

    return;
}



/**
 * \brief  ��ӡ����
 *
 * \param  score
 */
void ui_print_score(uint32_t score)
{
    gotoTextPos(33, 16);
    setTextColor(WHITE);
    printf("%4d", score);

    return;
}


/**
 * \brief  ��ӡ����
 *
 * \param  level 1 - N
 */
void ui_print_level(uint8_t level)
{
    gotoTextPos(33, 10);
    setTextColor(WHITE);
    printf("%4d", level);

    return;
}


/**
 * \brief  ��ӡ������
 *
 * \param  line
 */
void ui_print_line(uint16_t line)
{
    gotoTextPos(33, 13);
    setTextColor(WHITE);
    printf("%4d", line);

    return;
}


/**
 * \brief  print game over
 */
void ui_print_game_over(void)
{
    setTextColor(WHITE);
    gotoTextPos(4, 9);
    printf("                ");
    gotoTextPos(4, 10);
    printf("   GAME  OVER   ");
    gotoTextPos(4, 11);
    printf("                ");

    return;
}


/**
 * \brief  ����Ԥ��������Ϣ
 *
 * \param  brick
 */
void ui_print_preview(const void *info)
{
    bool bit;
    uint8_t x, y;
    uint16_t brick;

    const uint8_t *p_info = info;
    // ȡ�÷�������
    brick = (*(uint16_t *)p_info);

#ifdef UI_USE_COLOR
    uint8_t color;
    // ASCII C �в������ void ��ָ���������
    p_info += 2;
    // �õ���ɫֵ
    color = (*(uint8_t *)p_info);
#endif

    for (y = 0; y < 4; y++)
    {
        for (x = 0; x < 4; x++)
        {
            bit = ((brick & (0x0001 << (15 - (y * 4 + x)))) >> (15 - (y * 4 + x)));
            // ����ȫ�ǵ�һ���������ռ�������ַ�λ��
#ifdef UI_USE_COLOR
            if (bit)
                draw_box(x * 2 + PREVIEW_START_COLUMN, y + PREVIEW_START_ROW, color);
            else
                draw_box(x * 2 + PREVIEW_START_COLUMN, y + PREVIEW_START_ROW, 0);
#else
            draw_box(x * 2 + PREVIEW_START_COLUMN, y + PREVIEW_START_ROW, bit);
#endif
        }
    }

    return;
}




/**
 * \brief  print pause
 */
void ui_print_game_pause(void)
{
    setTextColor(WHITE);
    gotoTextPos(4, 8);
    printf("                ");
    gotoTextPos(4, 9);
    printf("     PAUSE      ");
    gotoTextPos(4, 10);
    printf(" Press ENTER to ");
    gotoTextPos(4, 11);
    printf("    continue    ");
    gotoTextPos(4, 12);
    printf("                ");

    return;
}



void ui_init(void)
{
    fixConsoleSize(42, 22);
    setCursorVisible(0);
    setConsoleTitle("Tetris by DevLabs");

    setTextColor(WHITE);
    gotoTextPos(0, 0);

    printf("������������������������              \n");
    printf("������������������������      Next    \n");
    printf("������������������������              \n");
    printf("������������������������    ��������  \n");
    printf("������������������������    ��������  \n");
    printf("������������������������    ��������  \n");
    printf("������������������������    ��������  \n");
    printf("������������������������              \n");
    printf("������������������������              \n");
    printf("������������������������              \n");
    printf("������������������������   ����:    1 \n");
    printf("������������������������              \n");
    printf("������������������������              \n");
    printf("������������������������   ����:    0 \n");
    printf("������������������������              \n");
    printf("������������������������              \n");
    printf("������������������������   ����:    0 \n");
    printf("������������������������              \n");
    printf("������������������������              \n");
    printf("������������������������   DevLabs.cn \n");
    printf("������������������������              \n");
    printf("������������������������                ");

    ui_print_line(0);
    ui_print_level(1);
    ui_print_score(0);

    // Ԥ��������Ϣ
    uint32_t temp = 0;
    ui_print_preview(&temp);

    return;
}


/************* Copyright(C) 2013 - 2014 DevLabs **********END OF FILE**********/


