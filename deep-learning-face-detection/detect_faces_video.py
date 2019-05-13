# USAGE
# python detect_faces_video.py --prototxt deploy.prototxt.txt --model res10_300x300_ssd_iter_140000.caffemodel

from imutils.video import VideoStream
import numpy as np
import argparse
import imutils
import time
import cv2
import os
import sys
from datetime import datetime

'''
人脸检测并标识
'''
def DetectAndPaint(win_name, frame, net, args):
    # grab the frame dimensions and convert it to a blob
	(h, w) = frame.shape[:2]
	blob = cv2.dnn.blobFromImage(cv2.resize(frame, (300, 300)), 1.0,
		(300, 300), (104.0, 177.0, 123.0))
	
	# pass the blob through the network and obtain the detections and
	# predictions
	net.setInput(blob)
	detections = net.forward()
	
	num =0 
	for i in range(0, detections.shape[2]):
	    # extract the confidence (i.e., probability) associated with the prediction
		confidence = detections[0, 0, i, 2]

		# filter out weak detections by ensuring the `confidence` is
		# greater than the minimum confidence
		if confidence < args["confidence"]:
			continue
		num = num +1
		# compute the (x, y)-coordinates of the bounding box for the
		# object
		box = detections[0, 0, i, 3:7] * np.array([w, h, w, h])
		(startX, startY, endX, endY) = box.astype("int")
 
		# draw the bounding box of the face along with the associated
		# probability
		text = "{:.2f}%".format(confidence * 100)
		y = startY - 10 if startY - 10 > 10 else startY + 10
		cv2.rectangle(frame, (startX, startY), (endX, endY),
			(0, 255, 0), 2)
		cv2.putText(frame, text, (startX, y),
			cv2.FONT_HERSHEY_SIMPLEX, 0.45, (0, 255, 0), 2)
			
	# show the output frame
	cv2.putText(frame,"cur num:",(20,20), cv2.FONT_HERSHEY_PLAIN,2.0,(0,255,0),2,1)
	cv2.putText(frame,str(num),(210,20),cv2.FONT_HERSHEY_PLAIN,2.0,(0,255,0),2,1)
	cv2.imshow(win_name, frame)   


'''
动态加载视频帧，对图像帧进行目标检测
'''
def ExecuteDetect(execTime, winName, args):  
	# load our serialized model from disk
	print("[INFO] loading model...")
	net = cv2.dnn.readNetFromCaffe(args["prototxt"], args["model"])
	
	# initialize the video stream and allow the cammera sensor to warmup
	print("[INFO] starting video stream...")
	cv2.namedWindow(winName)
	vs = VideoStream(src=0).start()
	time.sleep(1.0)
	
	start = datetime.now()
	# loop over the frames from the video stream
	while True:
		cur = datetime.now()
		dif = ChangeToSeconds(cur.hour-start.hour, cur.minute-start.minute, cur.second-start.second)
		if dif > execTime:
			print("时间到了，检测即将关闭...")
			break
		# grab the frame from the threaded video stream and resize it
		# to have a maximum width of 400 pixels
		frame = vs.read()
		frame = imutils.resize(frame, width=600)
	
		DetectAndPaint(winName, frame, net, args)
		
		# if the `q` key was pressed, break from the loop
		key = cv2.waitKey(1) & 0xFF
		if key == ord("q"):
			break
	
	# do a bit of cleanup
	vs.stop()
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
	# construct the argument parse and parse the arguments
	ap = argparse.ArgumentParser()
	ap.add_argument("-p", "--prototxt", required=True,
		help="path to Caffe 'deploy' prototxt file")
	ap.add_argument("-m", "--model", required=True,
		help="path to Caffe pre-trained model")
	ap.add_argument("-c", "--confidence", type=float, default=0.5,
		help="minimum probability to filter weak detections")
	args = vars(ap.parse_args())
	
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
		ExecuteDetect(seconds, "detecte window", args)
        #Hello(seconds)
