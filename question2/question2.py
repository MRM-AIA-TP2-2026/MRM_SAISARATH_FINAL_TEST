import cv2
import numpy as np


lower_hsv = np.array([0, 0, 200])
upper_hsv = np.array([180, 55, 255])



def cone(path):
    image=cv2.imread(path)

    lower_orange = np.array([10, 100, 100])
    upper_orange = np.array([25, 255, 255])

    blurred = cv2.GaussianBlur(image, (11, 11), 0)
    hsv = cv2.cvtColor(blurred, cv2.COLOR_BGR2HSV)
    mask = cv2.inRange(hsv, lower_hsv, upper_hsv)
    mask = cv2.erode(mask, None, iterations=2)
    mask = cv2.dilate(mask, None, iterations=2)
    contours, _ = cv2.findContours(mask.copy(), cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)

    center = None
    if contours:
        c = max(contours, key=cv2.contourArea)
        ((x, y), radius) = cv2.minEnclosingCircle(c)

    if radius > 10:
        cv2.circle(image, (int(x), int(y)), int(radius), (0, 255, 255), 2)
        cv2.circle(image, (int(x), int(y)), 5, (0, 0, 255), -1)
        cv2.putText(image, f"COne", (int(x) - 20, int(y) - 20),
                    cv2.FONT_HERSHEY_SIMPLEX, 0.6, (255, 0, 0), 2)

    cv2.imshow("Cone", image)

    cv2.waitKey(0)


cv2.destroyAllWindows()