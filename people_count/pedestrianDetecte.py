import cv2
import imutils
import numpy as np
import time
import os
import sys
from datetime import datetime
from apscheduler.schedulers.background import BackgroundScheduler


'''
人脸检测并标识
'''
def DetecteAndPaint(win_name, frame, face_cascade):
    i=frame
    # 图像预处理 
    gray = cv2.cvtColor(i, cv2.COLOR_BGR2GRAY)
    gray = imutils.resize(frame, width=min(700, frame.shape[1]))
    # 检测人脸
    faces = face_cascade.detectMultiScale(gray, 1.22, 4)
    l = len(faces) # 人脸个数
    #print (l)
    
    # 循环画出所有识别出的人脸框
    for(x,y,w,h) in faces:
        cv2.rectangle(i, (x,y), (x+w, y+h), (0,255,0), 2)
        cv2.putText(i,'face', (int(w/2+x),int(y-h/5)), cv2.FONT_HERSHEY_PLAIN,2.0,(0,255,0),2,1)
        roi_gray = gray[y:y+h, x:x+w]
        roi_coaclor = i[y:y+h, x:x+w]
        #eyes=eye_cascade.detectMultiScale(roi_gray)
        #for (ex,ey,ew,eh) in eyes:
            #cv2.rectangle(roi_color,(ex,ey),(ex+ew,ey+eh),(0,255,0),2)
            #cv2.putText(i,"eye_count",(20,60), cv2.FONT_HERSHEY_PLAIN,2.0,(255,255,255),2,1)
    # 画面显示统计结果
    cv2.putText(i,"cur num:",(20,20), cv2.FONT_HERSHEY_PLAIN, 2.0, (0,255,0), 2, 1)
    cv2.putText(i, str(l), (230,20), cv2.FONT_HERSHEY_PLAIN, 2.0, (0,255,0), 2, 1)
    cv2.imshow(win_name, i)


'''
动态加载视频帧，对图像帧进行目标检测
'''
def ExecuteDetect(execTime, winName):
    # 加载人脸级联器，进行稍后的人脸识别
    #face_cascade=cv2.CascadeClassifier(r"C:\Users\Tp\Anaconda3\envs\python37\Lib\site-packages\cv2\data\haarcascade_frontalface_default.xml")
    face_cascade=cv2.CascadeClassifier("/home/tp/.local/lib/python3.6/site-packages/cv2/data/haarcascade_frontalface_default.xml")
    
    cv2.namedWindow(winName)
    cap=cv2.VideoCapture(0)

    start = datetime.now()
    while cap.isOpened(): 
        cur = datetime.now()
        dif = ChangeToSeconds(cur.hour-start.hour, cur.minute-start.minute, cur.second-start.second)
        if dif > execTime:
            print("时间到了，检测即将关闭...")
            break
        ret,frame=cap.read()
        if not ret:  # 图像读取失败，break跳出循环
            break
        DetecteAndPaint(winName, frame, face_cascade)
        # 按q退出检测
        if cv2.waitKey(1) & 0xFF == ord('q'):
            break
    # 释放资源
    cap.release()
    cv2.destroyWindow(winName)
    print("摄像头已关闭！")

'''
将时间换算为总秒数
'''
def ChangeToSeconds(hour, minute, second):
    seconds = hour*60*60 
    seconds += minute*60 
    seconds +=second
    return seconds


'''
主执行函数
'''
if  __name__ == '__main__':
    while True:
        sys.stdin.flush( )
        str1= input("输入统计开始时间(00:00) : ")
        startHour = int(str1[0:2], 10)
        startMin = int(str1[2:4], 10)
        if startHour >= 24 and startMin >= 60:
            print("输入格式有误...")
        else:
            str1 = input( "输入需要检测持续时间 (单位/s):")
            seconds = int(str1, 10)
        while True:
            now = datetime.now( ) 
            if now.hour ==startHour and now.minute == startMin:
                print("任务启动中...")
                break
            print( "等待执行人数统计任务...")
            time.sleep(1)
        ExecuteDetect(seconds, "detecting window")
        #Hello(seconds)


#ExecuteDetect()
## 构造scheduler对象
#scheduler = BackgroundScheduler()
## 间隔3秒钟执行一次
#scheduler.add_job(func=ExecuteDetect, trigger='interval', seconds=15)
## 开启独立的一个线程执行任务
#scheduler.start()
#
#print('Press Ctrl+{0} to exit'.format('Break' if os.name == 'nt' else 'C'))
#
#try:
#    # 其他任务是独立的线程执行
#    while True:
#        print( "等待人脸检测任务中...")
#        time.sleep(1)
#except (KeyboardInterrupt, SystemExit):
#    scheduler.shutdown()
#    print("Exit the Job")

