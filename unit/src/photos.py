import cv2
import os


photos_path_prefix = "calibration"
x = max([int(i.replace(".jpg", "").replace(photos_path_prefix, "").replace("/calib", "").replace("/calibration", "")) for i in os.listdir(photos_path_prefix)]) + 1
print("Starting at %d" % x)

cap = cv2.VideoCapture(0)

while True:
    ret, frame = cap.read()

    cv2.imshow("Frame", frame)
    key = cv2.waitKey(1) & 0xFF
    if key == ord("q"):
        break
    if key == ord("c"):
        cv2.imwrite(os.path.join(photos_path_prefix, "calib{}.jpg".format(x)), frame)
        x += 1
