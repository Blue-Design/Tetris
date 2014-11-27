Tetris
======

һ�������õĶ���˹����ģ��

��Windows����̨������:

![Tetris](./Tetris.gif)

---

MSP430 Launchpad + PuTTY(�����ն�Ҳ��, ������115200, MCU������16MHz):

![Tetris](./Tetris_msp430.gif)

**ע: ͨѸ������Ϊ115200, lanuchpad�Դ���USBת���ڲ����ʴﲻ��, 
      Ϊ�˱�֤ͨѸ����, ��Ҫ�����USBת����ģ��**

---

��ģ��֮ǰ��������8051ϵ��΢�������ϵ�, �����ڴ�ռ�ú�С, ��֧�ֲ�ɫ.

��Ϸ���е�����߼����·������, ��ͼά��, �߽����ȫ��������װ��ģ���ڲ�, 
ʹ�ûص��������ⲿ����. ����Ҫ����, �����Լ���дUI�밴�������з���������غ���,
Ȼ����ģ���ʼ��ʱע��ģ������Ҫ�Ļص���������. ��Ϸ����߼���ȫ����Ҫ�����.

---

### ����˹������ظ������

����˹����Ļ���Ԫ����һ����4��С����������ɵĹ���ͼ�Σ���Ӣ�ĳ�ΪTetromino��
���������Ϊ����, Ӣ��д��**brick** . ������Tetromino��С�����γ�Ϊ**box**.  ����˹���鹲��7�����ͣ��ֱ���**S��Z��L��J��I��O��T**��7����ĸ����״��������

����Ķ���˹����**��ͼ��** �� 10 \* 20 ��box���.
�ڴ�ģ����, �趨��ͼ��ԭ��λ�����Ͻ�, ����Ϊ(0, 0).

---

### ��Ҫ�ṩ��ģ��Ļص�����:
+ ģ�鵼���Ľӿ�

```c
extern bool tetris_move(dire_t direction);
extern void tetris_sync(void);
extern void tetris_sync_all(void);
extern bool tetris_is_game_over(void);
extern void tetris_init(void (*draw_box_to_map)(uint8_t x, uint8_t y, uint8_t color),
                        uint8_t (*get_random)(void),
                        void (*next_brick_info)(const void *info),
                        void (*remove_line_num)(uint8_t line));
```

---

### �ӿ�˵��

+ extern bool tetris_move(dire_t direction);

��ĳ�������ƶ�����, ���õ�ȡֵΪ����ö������
```c
// direction
typedef enum
{
    dire_left,      //!< ����
    dire_right,     //!< ����
    dire_down,      //!< ����
    dire_rotate,    //!< ��ת
} dire_t;
```

+ extern void tetris_sync(void);
+ extern void tetris_sync_all(void);

���ǵ�Ч������, �����鱻�ƶ�����ʾ����������������, 
�������ⲿ��Ϊ���ʵ�ʱ����ʽ�ĵ�������������������ʾˢ��.
�������������������� tetris_sync(void) ֻ��ˢ�µ�ͼ�б仯�Ĳ���(���Ч��),
�� tetris_sync_all(void) ���ˢ��������ͼ(�����ڵ�ͼ��ʾ���������ʾ��������Ϣ
��ʹ��ͼ�����⵽�ƻ�).

+ extern bool tetris_is_game_over(void);
���ڵ�ͼ���޷������·���ʱ, ��Ϸ����, �˺�������**true**

+ extern void tetris_init()
ģ���ʼ������, ��Ҫע�Ἰ������Ļص�����:

1. remove_line_num(uint8_t line)

   ����������ʱ�ص��˺���, ����Ϊ����������.

2. draw_box_to_map(uint8_t x, uint8_t y, uint8_t color)

   �ڵ�ͼָ�������껭һ�������һ��**box**, ȡ���ڵ���������box��ֵ.
   color��ͬ����ֵ��ʾ��ͬ����ɫ, ��Ҫע�����,
   **����color��ֵΪ0ʱ��ʾ�����(x, y)�ϵ�box**.

3. get_random(void)

   ��ȡһ�������, ���ڲ����·���.

4. next_brick_info(const void *info)

   �˰汾�� *info Ϊ�޷���ʮ��λ����.
   �������·������һ���������Ϣ(����Ԥ��)����ص��˺�������.
   Ԥ���������Ϣʹ��һ���޷���16λ������ʾ, ÿ4bitһ��, Ϊ1�ĵط���ʾ��Ҫ����һ��box.
   ������ʮ�������� 0x0660, չ�������Ʒ���Ϊ:
```c
                    0000    // bit15 - bit12
                    0110    // bit11 - bit8
                    0110    // bit7  - bit4
                    0000    // bit3  - bit0
```
   ����ʮ����������ʾһ��O�͵ķ���.

��platfrom/windows������Windows����̨��ʵ�ֵĴ���, ���ο�.
�����װ��GCC, ����builder.bat��ֱ�ӱ���.
���ʹ��IDE���Խ����е�.c�ļ���.h�ļ�����һ���ļ�����ӽ����̱��뼴��.

--- 

MSP430ƽ̨�Ĵ���ʹ��IAR for msp430 v5.5 ����, ���ļ���IAR���Ƕ�Ӧ�Ĺ����ļ�,
�򿪼��ɱ���.

