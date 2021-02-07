# Automatic_Recycle_Machine
아두이노를 기반으로 만든 자동 분리수거 쓰레기통입니다.

<img src="https://user-images.githubusercontent.com/78673090/107138552-57711780-6958-11eb-8bd5-e4bed43123b6.png" width="600" height="300">

## 프로젝트 동작 설명 및 도면

1. 물체를 투입하면 1차 분류대에서는 적외선 센서로 물체의 투입 여부를 파악
2. 금속감지 센서를 이용하여 금속, 비금속을 결정
3. 1차 분류대에서 비금속으로 분류된 물체는 2차 분류대로 떨어짐
4. 2차 분류대의 로드셀 센서를 이용하여 떨어지는 물체의 무게를 감지
5. 유리와 플라스틱이 떨어질 때의 무게에 대한 threshold 값을 정하여 기준값에 대한 분류

<img src="https://user-images.githubusercontent.com/78673090/107137962-8be2d480-6954-11eb-95e9-86246d17b06d.png" width="370" height="300">

<img src="https://user-images.githubusercontent.com/78673090/107138355-44117c80-6957-11eb-997a-438cead22395.png" width="600" height="300">

## 사용 부품

1. 아두이노 메가 보드
2. 적외선 센서
3. 금속 감지 센서
4. 로드셀 무게 감지 센서
5. HX711 로드셀 앰프 증폭 모듈
6. LED
7. 외부 전원(9V)
