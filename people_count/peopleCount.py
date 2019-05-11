# import the necessary packages
from __future__ import print_function
from imutils.object_detection import non_max_suppression
from imutils import paths
import numpy as np
import argparse
import imutils
import cv2

#cap=cv2.VideoCapture(r'E:\搜狗高速下载\JiJiDown\Download\running1.mp4')
cap=cv2.VideoCapture(0)

# initialize the HOG descriptor/person detector
hog = cv2.HOGDescriptor()
hog.setSVMDetector(cv2.HOGDescriptor_getDefaultPeopleDetector())

def showPeopleNum(picture_frame, nms_frame):
	num =len(nms_frame)
	for (xA, yA, xB, yB) in nms_frame:
		cv2.rectangle(picture_frame, (xA, yA), (xB, yB), (0, 255, 0), 1)  #绿色画出识别处对象方框
	cv2.putText(picture_frame,"num:",(20,20), cv2.FONT_HERSHEY_PLAIN,1.0,(0,255,0),2,1)
	cv2.putText(picture_frame, str(num),(70,20),cv2.FONT_HERSHEY_PLAIN,1.4,(0,255,0),2,1)
	cv2.imshow("people_count", picture_frame)
	
	
if __name__ == '__main__':
	while True:
		# load the image and resize it to (1) reduce detection time
		# and (2) improve detection accuracy
		ret,frame=cap.read()
		img_show = imutils.resize(frame, width=min(450, frame.shape[1]))
		image = cv2.cvtColor(img_show, cv2.COLOR_BGR2GRAY)
		#orig = image.copy()
		
		# detect people in the image
		(rects, weights) = hog.detectMultiScale(image, winStride=(4, 4), padding=(8, 8), scale=1.045)
		
		# apply non-maxima suppression to the bounding boxes using a
		# fairly large overlap threshold to try to maintain overlapping
		# boxes that are still people
		rects = np.array([[x, y, x + w, y + h] for (x, y, w, h) in rects])
		pick = non_max_suppression(rects, probs=None, overlapThresh=0.65) #nms法	
		# draw the final bounding boxes	
		showPeopleNum(img_show, pick)
		if cv2.waitKey(1)& 0xff == ord('q'):
			exit(0)




#import cv2
#import numpy as np
#
#face_cascade=cv2.CascadeClassifier(r"F:\Anaconda\envs\python37\Lib\site-packages\cv2\data\haarcascade_frontalface_default.xml")
#eye_cascade=cv2.CascadeClassifier(r"F:\Anaconda\envs\python37\Lib\site-packages\cv2\data\haarcascade_eye.xml")
#cap=cv2.VideoCapture(r'E:\搜狗高速下载\JiJiDown\Download\running.mp4')
#
#
#while (True):
#	ret,frame=cap.read()
#	i=frame
#    #print i.shape
#	gray=cv2.cvtColor(i,cv2.COLOR_BGR2GRAY)
#	faces=face_cascade.detectMultiScale(gray,1.22,5)
#	l=len(faces)
#	print (l)
#	for(x,y,w,h) in faces:
#		cv2.rectangle(i, (x,y), (x+w, y+h), (255,0,0), 2)
#		cv2.putText(i,'face',(int(w/2+x),int(y-h/5)),cv2.FONT_HERSHEY_PLAIN,2.0,(255,0,0),2,1)
#		roi_gray = gray[y:y+h, x:x+w]
#		roi_color = i[y:y+h, x:x+w]
#		cv2.putText(i,"face_count",(20,20), cv2.FONT_HERSHEY_PLAIN,2.0,(255,0,0),2,1)
#		cv2.putText(i,str(l),(230,20),cv2.FONT_HERSHEY_PLAIN,2.0,(255,0,0),2,1)
#		#eyes=eye_cascade.detectMultiScale(roi_gray)
#		#for (ex,ey,ew,eh) in eyes:
#		#	cv2.rectangle(roi_color,(ex,ey),(ex+ew,ey+eh),(0,255,0),2)
#		#	
#		#	
#		#	#cv2.putText(i,"eye_count",(20,60), cv2.FONT_HERSHEY_PLAIN,2.0,(255,255,255),2,1)
#	cv2.imshow("rstp",i)
#	if cv2.waitKey(1) & 0xFF == ord('q'):
#	    exit(0)
