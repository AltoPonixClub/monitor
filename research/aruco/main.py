import cv2
import numpy as np

img = cv2.imread('arucoBoard.png')
#read in webcam
cap = cv2.VideoCapture(0)


#cycle through webcam
while(True):
    # Capture frame-by-frame
    ret, frame = cap.read()
    # Our operations on the frame come here
    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    aruco_dict = cv2.aruco.Dictionary_get(cv2.aruco.DICT_6X6_250)
    parameters = cv2.aruco.DetectorParameters_create()
    corners, ids, rejectedImgPoints = cv2.aruco.detectMarkers(gray, aruco_dict, parameters=parameters)

    k = np.load("calibration_matrix.npy")
    d = np.load("distortion_coefficients.npy")


    if ids is not None and len(ids) > 0:
        cv2.aruco.drawDetectedMarkers(frame, corners, ids, (0, 255, 0))

    if ids is not None and len(ids) > 0:
        for i in range(0, len(ids)):
            rvecs, tvecs, _ = cv2.aruco.estimatePoseSingleMarkers(corners[i], 0.05, k, d)
            (rvecs - tvecs).any()
            cv2.aruco.drawAxis(frame,
                               k,
                               d,
                               rvecs,
                               tvecs,
                               0.5)

    cv2.imshow('frame',frame)
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

cv2.destroyAllWindows()