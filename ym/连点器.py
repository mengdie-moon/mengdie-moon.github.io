import time
import pyautogui
import keyboard

a = int(input('点击次数：'))
b = float(input('点击间隔/S:'))
c = float(input('请输入将鼠标移动至指定位置所需的时间：'))

while c >= 0:
    print(c,'S内将鼠标移动至指定位置')
    time.sleep(1)
    c -= 1

d = pyautogui.position()

print('开始运行')
print('点击Esc键可以退出')

while a > 0:
    pyautogui.click(d[0],d[1])
    a -= 1
    time.sleep(b)
    if keyboard.is_pressed('Esc'):
       break