import cv2
 
# 初始化摄像头
cap = cv2.VideoCapture(0)  # 0 通常是默认摄像头的标识
 
# 检查摄像头是否成功打开
if not cap.isOpened():
    print("无法打开摄像头")
    exit()
 
# 读取摄像头的帧
while True:
    # 读取帧
    ret, frame = cap.read()
    
    # 如果正确读取帧，ret为True
    if not ret:
        print("无法接收帧，请退出")
        break
    
    # 展示帧
    cv2.imshow('Camera', frame)
    
    # 按 'q' 退出循环
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break
 
# 释放摄像头资源
cap.release()
# 关闭所有OpenCV窗口
cv2.destroyAllWindows()