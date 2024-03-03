import cv2
import subprocess
# from python_imagesearch import four_point_transform
from skimage.filters import threshold_local #check this 
import numpy as np

import imutils


from PIL import Image

def order_points(pts):
	# initialzie a list of coordinates that will be ordered
	# such that the first entry in the list is the top-left,
	# the second entry is the top-right, the third is the
	# bottom-right, and the fourth is the bottom-left
	rect = np.zeros((4, 2), dtype = "float32")
	# the top-left point will have the smallest sum, whereas
	# the bottom-right point will have the largest sum
	s = pts.sum(axis = 1)
	rect[0] = pts[np.argmin(s)]
	rect[2] = pts[np.argmax(s)]
	# now, compute the difference between the points, the
	# top-right point will have the smallest difference,
	# whereas the bottom-left will have the largest difference
	diff = np.diff(pts, axis = 1)
	rect[1] = pts[np.argmin(diff)]
	rect[3] = pts[np.argmax(diff)]
	# return the ordered coordinates
	return rect

def four_point_transform(image, pts):
	# obtain a consistent order of the points and unpack them
	# individually
	rect = order_points(pts)
	(tl, tr, br, bl) = rect
	# compute the width of the new image, which will be the
	# maximum distance between bottom-right and bottom-left
	# x-coordiates or the top-right and top-left x-coordinates
	widthA = np.sqrt(((br[0] - bl[0]) ** 2) + ((br[1] - bl[1]) ** 2))
	widthB = np.sqrt(((tr[0] - tl[0]) ** 2) + ((tr[1] - tl[1]) ** 2))
	maxWidth = max(int(widthA), int(widthB))
	# compute the height of the new image, which will be the
	# maximum distance between the top-right and bottom-right
	# y-coordinates or the top-left and bottom-left y-coordinates
	heightA = np.sqrt(((tr[0] - br[0]) ** 2) + ((tr[1] - br[1]) ** 2))
	heightB = np.sqrt(((tl[0] - bl[0]) ** 2) + ((tl[1] - bl[1]) ** 2))
	maxHeight = max(int(heightA), int(heightB))
	# now that we have the dimensions of the new image, construct
	# the set of destination points to obtain a "birds eye view",
	# (i.e. top-down view) of the image, again specifying points
	# in the top-left, top-right, bottom-right, and bottom-left
	# order
	dst = np.array([
		[0, 0],
		[maxWidth - 1, 0],
		[maxWidth - 1, maxHeight - 1],
		[0, maxHeight - 1]], dtype = "float32")
	# compute the perspective transform matrix and then apply it
	M = cv2.getPerspectiveTransform(rect, dst)
	warped = cv2.warpPerspective(image, M, (maxWidth, maxHeight))
	# return the warped image
	return warped

def equalArray(array1, array2):
    same = True
    #print("arrays:\n")
    #print(array1)
    #print(array2)
    if len(array1) != len(array2):
        return False
    
    for i in range(len(array1)):
        for j in range(1):
            for k in range(2):
                if abs(array1[i][j][k] - array2[i][j][k]) > 50:
                    same = False
    return same

print("test")
video = cv2.VideoCapture(0, cv2.CAP_DSHOW) # change for camera 

codec = 0x47504A4D  # MJPG
#video.set(cv2.CAP_PROP_FPS, 30.0)
#video.set(cv2.CAP_PROP_FOURCC, cv2.VideoWriter.fourcc('m','j','p','g'))
#video.set(cv2.CAP_PROP_FOURCC, cv2.VideoWriter.fourcc('M','J','P','G'))
#video.set(cv2.CAP_PROP_FRAME_WIDTH, 1920*2)
#video.set(cv2.CAP_PROP_FRAME_HEIGHT, 1080*2)

if not video.isOpened():
	print("Failed to open camera")
	exit()
else:
    print("video opened")

consec = 0
lastCnt = [[[None, None], [None, None], [None, None], [None, None]]]

while True:
	# reads a frame from video
	ret, image = video.read()
	# print(ret)
	if not ret:
		print("Frame reading error.")
		continue

	'''
	# construct the argument parser and parse the arguments
	ap = argparse.ArgumentParser()
	ap.add_argument("-i", "--image", required = True, 
		help = "Path to the image to be scanned")               # --image is the file to be input 
	args = vars(ap.parse_args())
	'''

	# load the image and compute the ratio of the old height
	# to the new height, clone it, and resize it
	# image = cv2.imread(args["image"])
		# ratio = image.shape[0] / 500.0
	orig = image.copy()
		# image = imutils.resize(image, height = 500)
	# convert the image to grayscale, blur it, and find edges
	# in the image
	gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
	gray = cv2.GaussianBlur(gray, (5, 5), 0)
	edged = cv2.Canny(gray, 75, 200)
	# show the original image and the edge detected image
	#print("STEP 1: Edge Detection")
	# cv2.imshow("Image", image)
	# cv2.imshow("Edged", edged)
	# cv2.waitKey(0)
	# cv2.destroyAllWindows()

	# find the contours in the edged image, keeping only the
	# largest ones, and initialize the screen contour
	cnts = cv2.findContours(edged.copy(), cv2.RETR_LIST, cv2.CHAIN_APPROX_SIMPLE)
	cnts = imutils.grab_contours(cnts)
	cnts = sorted(cnts, key = cv2.contourArea, reverse = True)[:5]
	detected = False
	# loop over the contours 
	for c in cnts:
		# approximate the contour
		peri = cv2.arcLength(c, True)
		approx = cv2.approxPolyDP(c, 0.02 * peri, True)
		# if our approximated contour has four points, then we
		# can assume that we have found our screen
		if len(approx) == 4:
			screenCnt = approx
			#print("+1 quad")
			detected = True
			break
	# cv2.drawContours(image, approx, -1, (0, 0, 255), 2)
	# show the contour (outline) of the piece of paper
	#print("STEP 2: Find contours of paper")
	if detected:
		cv2.drawContours(image, [screenCnt], -1, (0, 255, 0), 2)
		if lastCnt[0][0][0] != None and equalArray(lastCnt, screenCnt):
			consec += 1
		else:
			consec = 0
		lastCnt = screenCnt
	cv2.imshow("Outline", image)
	# cv2.waitKey(0)
	# cv2.destroyAllWindows() 
 
	if consec == 50:	# adjust waitkey() to adjust frame rate
		# apply the four point transform to obtain a top-down
		# view of the original image
		warped = four_point_transform(orig, screenCnt.reshape(4, 2))  # * ratio
		# convert the warped image to grayscale, then threshold it
		# to give it that 'black and white' paper effect
		warped = cv2.cvtColor(warped, cv2.COLOR_BGR2GRAY)
		# T = threshold_local(warped, 11, offset = 5, method = "gaussian")
		# warped = (warped > T).astype("uint8") * 255
		# ret, warped = cv2.threshold(gray, 0, 255, cv2.THRESH_BINARY_INV + cv2.THRESH_OTSU)
		# show the original and scanned images
		contours, _ = cv2.findContours(warped, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
		# Draw contours on original image
		output = warped.copy()
		#output = cv2.resize(output, (1750, 1350))
		cv2.drawContours(output, contours, -1, (0, 255, 0), 2)
		print("STEP 3: Apply perspective transform")
		cv2.destroyAllWindows()
		video.release()
		cv2.imshow("Original", orig)
		cv2.imshow("Scanned", output)
		if cv2.waitKey(0) & 0xFF == ord('g'):		# adjust waitkey() to adjust frame rate
			'''warped = cv2.resize(warped, (1750, 1350))
			allWhite = [True]*len(warped)
			for i in len(warped):
				for j in len(len(warped)):
					if warped[i][j] <= 150:	
						allWhite[i] = False
						break
			print(allWhite)
			line = 0
			breaks = np.array()
			while (line < len(allWhite)):
				if allWhite[line]:
					index1 = line
					while(allWhite[line]):
						line += 1
					index2 = line - 1
					np.append(breaks, (index1+index2)/2)'''
			cv2.imwrite("C:\\Users\\anish\\OneDrive\\Desktop\\twinkle.png", warped, [cv2.IMWRITE_PNG_COMPRESSION, 0])
			im = Image.open("C:\\Users\\anish\\OneDrive\\Desktop\\twinkle.png")
			im.save("C:\\Users\\anish\\OneDrive\\Desktop\\twinkleDPI.png", dpi=(300, 300))
		break
	elif cv2.waitKey(33) &0xFF == ord('b'):
		break

video.release()
cv2.destroyAllWindows()
# end of camera, convert img to mxl
subprocess.call("converter.py",shell=True)