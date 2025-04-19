import cv2
import subprocess
import os
from skimage.filters import threshold_local #check this 
import numpy as np
from MusicXMLChecker import *
import imutils
from PIL import Image

output_location = fr"C:\Users\Error\Desktop\OEMER\PNG Files\CheckerTest.png"
output_xml_location = fr"C:\Users\Error\Desktop\OEMER\XML Files\Fluke3.musicxml"

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
video.set(cv2.CAP_PROP_FRAME_WIDTH, 1920)
video.set(cv2.CAP_PROP_FRAME_HEIGHT, 1080)

if not video.isOpened():
	print("Failed to open camera")
	exit()
else:
    print("video opened")

consec = 0
lastCnt = [[[None, None], [None, None], [None, None], [None, None]]]
isValidXML = False
while not isValidXML:
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
	#gray = cv2.GaussianBlur(gray, (5, 5), 0)

	# Original Sharpen
	sharpen = cv2.GaussianBlur(gray, (0,0), 3)
	sharpen = cv2.addWeighted(gray, 1.5, sharpen, -0.5, 0)

	# ALTERNATIVE SHARPEN
	'''
	kernel = np.array([[-1, -1, -1],
						[-1, 9, -1],
						[-1, -1, -1]])
	sharpen = cv2.filter2D(gray, -1, kernel)
	'''

	# Denoise
	'''sharpen = cv2.fastNlMeansDenoisingColored(gray, None, 10, 10, 7, 21)'''

	# Upscale
	'''sharpen = cv2.resize(gray, None, fx=2, fy=2, interpolation=cv2.INTER_CUBIC)'''

	# Alpha Adjust
	'''sharpen = cv2.convertScaleAbs(gray, alpha=1.2, beta=10)'''

	# Will update blurriness in terminal while it's running
	fm = cv2.Laplacian(gray, cv2.CV_64F).var()
	if fm < 50:
		print("Image is blurry")
	else:
		print("Image is not blurry")

	thresh = cv2.adaptiveThreshold(sharpen, 255, cv2.ADAPTIVE_THRESH_GAUSSIAN_C, cv2.THRESH_BINARY, 21, 15)


	#laplacian = cv2.Laplacian(gray, cv2.CV_64F, ksize=5)
	#laplacian = np.uint8(np.absolute(laplacian))  # Convert to unsigned 8-bit integer

	# Optionally, normalize to [0, 255] range
	#laplacian = cv2.normalize(laplacian, None, 0, 255, cv2.NORM_MINMAX)

	# Show the Laplacian edge-detected image
	#cv2.imshow("Laplacian Edges", thresh)

	# Apply Sobel edge detection instead of Canny
	sobelX = cv2.Sobel(gray, cv2.CV_64F, 1, 0, ksize=5)  # Sobel in the X direction
	sobelY = cv2.Sobel(gray, cv2.CV_64F, 0, 1, ksize=5)  # Sobel in the Y direction
	sobel = cv2.sqrt(sobelX ** 2 + sobelY ** 2)           # Combine both directions

	# Convert back to uint8 type since the values are floating-point
	sobel = np.uint8(np.absolute(sobel))

	# Optionally, normalize to [0, 255] range
	sobel = cv2.normalize(sobel, None, 0, 255, cv2.NORM_MINMAX)

	# Show the Sobel edge-detected image
	#cv2.imshow("Sobel Edges", sobel)

	# TODO 
	edged = cv2.Canny(gray, 75, 200)
	rotated = cv2.rotate(edged, cv2.ROTATE_90_CLOCKWISE)
	rotated = cv2.resize(rotated, (360, 640))
	cv2.imshow("Canny Edges", rotated)
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
	image = cv2.rotate(image, cv2.ROTATE_90_CLOCKWISE)
	image = cv2.resize(image, (360, 640))
	cv2.imshow("Outline", image)
	# cv2.waitKey(0)
	# cv2.destroyAllWindows() 
 
	# This is how we determine how long before it takes the photo
	# Wait Time
	# adjust consec to adjust camera wait time
	# press f to prematurely take an image
	if consec == 30 or (cv2.waitKey(33) & 0xFF == ord('f')): # adjust waitkey() to adjust frame rate
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
		#video.release()
		output = cv2.rotate(output, cv2.ROTATE_90_CLOCKWISE)
		orig = cv2.rotate(orig, cv2.ROTATE_90_CLOCKWISE)
		cv2.imshow("Original", orig)
		cv2.imshow("Scanned", output)
		if cv2.waitKey(0) & 0xFF == ord('g'):		# adjust waitkey() to adjust frame rate
			warped = cv2.rotate(warped, cv2.ROTATE_90_CLOCKWISE)
			cv2.imwrite(output_location, warped, [cv2.IMWRITE_PNG_COMPRESSION, 0])
			im = Image.open(output_location)
			im.save(output_location, dpi=(300, 300))
			cv2.destroyAllWindows()

			# end of camera, convert img to mxl
			#print("calling image to XML")
			#command = fr'cmd /c ""C:\Users\Error\AppData\Roaming\Microsoft\Windows\Start Menu\Programs\Audiveris\Audiveris.lnk" -batch -output "C:\Users\Error\Desktop\OEMER\XML Files" -export -- "C:\Users\Error\Desktop\OEMER\PNG Files\test.png"'
			#command = r'"C:\Users\Edward\AppData\Roaming\Microsoft\Windows\Start Menu\Programs\Audiveris\Audiveris.lnk" -batch -output "C:\\Users\\Edward\\Desktop\\Piano Hand Output" -export -- "C:\\Users\\Edward\\Desktop\\Piano Hand Output\\twinkle.png"'
			command = 'oemer -o \"' + output_xml_location + '\" --without-deskew \"' + output_location + '\"'
			os.system(command)
			#os.system("C:\\Users\\Edward\\arc-piano-hand\\perception\\img2mxl.py")
			#subprocess.call("C:\\Users\\Edward\\arc-piano-hand\\perception\\img2mxl.py",shell=True)
			checker = MusicXMLChecker(output_xml_location)
			isValidXML = checker.verifyAll()
			if (not isValidXML):
				print("This musicXML was not valid")

			else:
				print("We are good to send to algorithms")
				break
	elif cv2.waitKey(33) &0xFF == ord('b'): # Exits the camera please keep this in mind.
		break

video.release()
cv2.destroyAllWindows()