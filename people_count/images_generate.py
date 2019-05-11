import cv2
cam=cv2.VideoCapture( 0)
face_cascade=cv2.CascadeClassifier("/home/tp/.local/lib/python3.6/site-packages/cv2/data/haarcascade_frontalface_default.xml")

#Id = input( "enter id for reconition:")
# 图片样本数量
sampleNum=0
while True:
    ret,img = cam.read( ) 
    gray = cv2.cvtColor( img, cv2.COLOR_BGR2GRAY)

    faces = face_cascade.detectMultiScale( gray, 1.2, 3)
    for (x,y,w,h) in faces:
        cv2.rectangle( img, ( x,y), ( x+w,y+h), ( 255,0,0), 2)

        sampleNum += 1
        #cv2.imwrite("/home/tp/imagesDb/image."+ str(sampleNum)+ ".jpg", gray[y:y+h, x:x+w])
        cv2.imwrite('/home/tp/people_count/imagesDb/'+str(sampleNum)+'.jpg', gray[y:y+h, x:x+w])
        cv2.imshow('frame', img)
    if cv2.waitKey(100) & 0xff == ord( 'q'):
       break
    elif sampleNum>20:
       break

cam.release( )
cv2.destroyAllWindows( )
