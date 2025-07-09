# 🎯 엣지 디바이스에서 객체 인식하기 with Edge Impulse FOMO

이 문서에서는 Edge Impulse의 FOMO(Object Detection) 알고리즘을 이용해 **마이크로컨트롤러 기반 엣지 디바이스**에서 객체를 실시간으로 인식하는 전체 과정을 소개합니다.

---

## 🧠 FOMO란?

**FOMO (Faster Objects, More Objects)**는 Edge Impulse가 만든 객체 인식 알고리즘입니다.

![FOMO 기술 소개](https://docs.edgeimpulse.com/docs/~gitbook/image?url=https%3A%2F%2F3586622393-files.gitbook.io%2F%7E%2Ffiles%2Fv0%2Fb%2Fgitbook-x-prod.appspot.com%2Fo%2Fspaces%252FGEgcCk4PkS5Pa6uBabld%252Fuploads%252Fgit-blob-7f8499ac4bd6d22d37204e7d5e59724aea3b50c9%252F503f3af-ai.png%3Falt%3Dmedia&width=400&dpr=3&quality=100&sign=f483abff&sv=2)
_▲ FOMO (Faster Objects, More Objects) - 엣지 디바이스용 실시간 객체 감지_

- YOLO/SSD와 다르게 **Bounding Box 대신 중심점(Centroid)** 을 예측합니다.
- **200KB 이하 RAM**에서도 구동 가능 (ESP32, STM32 등)
- **YOLO보다 30배 빠름**, 소형 장치에서도 객체 추적·카운팅 지원

**한계점**

- 객체의 크기 정보는 없음
- 객체가 너무 붙어있으면 정확도 저하 가능
- 유사한 크기의 객체에 최적화됨

---

## 📦 준비물

- Edge Impulse 계정
- ESP32-CAM, Raspberry Pi, Jetson Nano 등 지원되는 장치
- 또는 스마트폰/카메라 → 이미지 업로드

---

## 1️⃣ 데이터 수집 및 라벨링

- Edge Impulse Studio에서 **Data acquisition → Upload** 또는 장치 연결로 데이터 수집
- `Labeling queue`에서 **Bounding box 기반 라벨링**
- YOLOv5, 기존 모델, Object tracking 기반 **AI Assisted Labeling**도 가능

> 예: 자동차 데이터 → YOLOv5로 90% 이상 자동 라벨링 가능

---

## 2️⃣ Impulse 구성

1. `Create Impulse` 탭에서:
   - Input: Image (96×96, Grayscale)
   - Resize mode: Fit shortest axis
   - Add blocks: `Images` + `Object Detection (Images)`
2. `Save Impulse`
   ![엣지 디바이스 예시](https://docs.edgeimpulse.com/docs/~gitbook/image?url=https%3A%2F%2F3586622393-files.gitbook.io%2F%7E%2Ffiles%2Fv0%2Fb%2Fgitbook-x-prod.appspot.com%2Fo%2Fspaces%252FGEgcCk4PkS5Pa6uBabld%252Fuploads%252Fgit-blob-000878f1efa95604fb8483c25197b8b37a132cb6%252Fimpulse.PNG%3Falt%3Dmedia&width=768&dpr=4&quality=100&sign=54d38c60&sv=2)
   _▲ 엣지 디바이스에서의 실시간 AI 추론_

---

## 3️⃣ 전처리 및 특징 추출

- `Images` → RGB/Grayscale 선택 후 `Save Parameters`
- `Generate Features` 버튼 클릭
- Feature Explorer를 통해 **클러스터 구조 시각화**

![데이터 라벨링 시스템](https://docs.edgeimpulse.com/docs/~gitbook/image?url=https%3A%2F%2F3586622393-files.gitbook.io%2F%7E%2Ffiles%2Fv0%2Fb%2Fgitbook-x-prod.appspot.com%2Fo%2Fspaces%252FGEgcCk4PkS5Pa6uBabld%252Fuploads%252Fgit-blob-67f6a44d1a89eba091417a89f7f4e32c1c5b72bc%252Fraw.PNG%3Falt%3Dmedia&width=768&dpr=4&quality=100&sign=7f4cdf4d&sv=2)

![데이터 라벨링 시스템](https://docs.edgeimpulse.com/docs/~gitbook/image?url=https%3A%2F%2F3586622393-files.gitbook.io%2F%7E%2Ffiles%2Fv0%2Fb%2Fgitbook-x-prod.appspot.com%2Fo%2Fspaces%252FGEgcCk4PkS5Pa6uBabld%252Fuploads%252Fgit-blob-fedae48f84bd112374219d3726f30979c3234d6d%252Fstudio-fomo-feature-explorer.png%3Falt%3Dmedia&width=768&dpr=4&quality=100&sign=9656f802&sv=2)
_▲ Edge Impulse Studio의 데이터 라벨링 시스템_

---

## 4️⃣ 모델 학습

- `Object Detection` 탭 → `Choose a different model` → FOMO 선택
- Learning Rate: 0.001 권장
- 학습 완료 후 **F1 Score, Precision, Recall** 등 확인 가능
- FOMO는 **모바일넷 V2 기반**으로 전이학습 가능

![데이터 라벨링 시스템](https://docs.edgeimpulse.com/docs/~gitbook/image?url=https%3A%2F%2F3586622393-files.gitbook.io%2F%7E%2Ffiles%2Fv0%2Fb%2Fgitbook-x-prod.appspot.com%2Fo%2Fspaces%252FGEgcCk4PkS5Pa6uBabld%252Fuploads%252Fgit-blob-faf97714af78e129ce0ee395b0273717a1ad6aa2%252Fecdcc66-fom1.png%3Falt%3Dmedia&width=768&dpr=4&quality=100&sign=af3e41cc&sv=2)

![](https://docs.edgeimpulse.com/docs/~gitbook/image?url=https%3A%2F%2F3586622393-files.gitbook.io%2F%7E%2Ffiles%2Fv0%2Fb%2Fgitbook-x-prod.appspot.com%2Fo%2Fspaces%252FGEgcCk4PkS5Pa6uBabld%252Fuploads%252Fgit-blob-696123031ea847fb346708a33ae7e08e95572c1a%252Fd47241d-eval.png%3Falt%3Dmedia&width=400&dpr=3&quality=100&sign=56c67df9&sv=2)

---

## 5️⃣ 테스트 및 Live Classification

- 수집한 데이터 중 20%는 테스트셋으로 분리
- `Model Testing` → `Classify All`
- `Live Classification` → 예측 결과 이미지와 오버레이 비교

예시:

- 실제 차량 18대 중 16대 정확히 탐지 → Precision 100%, Recall 63.6%, F1 Score 77.78%

![주차장 점유율 감지](https://docs.edgeimpulse.com/docs/~gitbook/image?url=https%3A%2F%2F3586622393-files.gitbook.io%2F%7E%2Ffiles%2Fv0%2Fb%2Fgitbook-x-prod.appspot.com%2Fo%2Fspaces%252FGEgcCk4PkS5Pa6uBabld%252Fuploads%252Fgit-blob-0513d000084c563d29db248ec57b2f11af7bfbae%252F2577da3-test.png%3Falt%3Dmedia&width=768&dpr=4&quality=100&sign=d8ce9668&sv=2)

![](https://docs.edgeimpulse.com/docs/~gitbook/image?url=https%3A%2F%2F3586622393-files.gitbook.io%2F%7E%2Ffiles%2Fv0%2Fb%2Fgitbook-x-prod.appspot.com%2Fo%2Fspaces%252FGEgcCk4PkS5Pa6uBabld%252Fuploads%252Fgit-blob-5abf400d7e9c51b70e65ec7c4dbbb2284ad43a0b%252Fb743a20-fomokim.png%3Falt%3Dmedia&width=768&dpr=4&quality=100&sign=7b01074b&sv=2)
_▲ FOMO를 활용한 주차장 점유율 실시간 모니터링_

## 6️⃣ 디바이스 배포 및 실시간 실행

- `Deployment` 탭 → Arduino Library 또는 Linux Binary 생성
- Arduino IDE:
  - Sketch → Include Library → Add .ZIP
  - 예제 실행: `Examples from Custom Library` → 업로드
- Raspberry Pi:
  ```bash
  edge-impulse-linux-runner
  ```

웹에서 실시간 확인:  
http://[장치IP]:[포트]  
예) http://192.168.8.117:4912

![하이브리드 클라우드-엣지 구조](https://docs.edgeimpulse.com/docs/~gitbook/image?url=https%3A%2F%2F3586622393-files.gitbook.io%2F%7E%2Ffiles%2Fv0%2Fb%2Fgitbook-x-prod.appspot.com%2Fo%2Fspaces%252FGEgcCk4PkS5Pa6uBabld%252Fuploads%252Fgit-blob-888f8fe6e2cbfc8909a03125738d9c1fb48fcbea%252Ff3ef00b-Screenshot_2022-03-30_at_15.05.37.png%3Falt%3Dmedia&width=768&dpr=4&quality=100&sign=ba384079&sv=2)

---

## 🧪 예제 코드 (Arduino with ESP32-CAM)

```cpp
#include <whiteball_inferencing.h>
...
bool ei_camera_capture(...) {
    ...
    run_classifier(&signal, &result, false);
    for (int i = 0; i < result.bounding_boxes_count; i++) {
        ei_printf("%s (%f) [x:%u, y:%u, w:%u, h:%u]\n",
            result.bounding_boxes[i].label,
            result.bounding_boxes[i].value,
            result.bounding_boxes[i].x,
            result.bounding_boxes[i].y,
            result.bounding_boxes[i].width,
            result.bounding_boxes[i].height);
    }
}
```

## ![](https://docs.edgeimpulse.com/docs/~gitbook/image?url=https%3A%2F%2F3586622393-files.gitbook.io%2F%7E%2Ffiles%2Fv0%2Fb%2Fgitbook-x-prod.appspot.com%2Fo%2Fspaces%252FGEgcCk4PkS5Pa6uBabld%252Fuploads%252Fgit-blob-e55c36d1317f32d37ff13a5cade54a24a1e98ac2%252F8547014-portfomo.png%3Falt%3Dmedia&width=768&dpr=4&quality=100&sign=1d077d5c&sv=2)

## ✅ 요약

| 항목      | 설명                                                       |
| --------- | ---------------------------------------------------------- |
| 목적      | 초저가 엣지 디바이스에서 실시간 객체 인식                  |
| 알고리즘  | FOMO (Centroid 기반, 경량)                                 |
| 장점      | 빠르고 가벼움, 실시간 처리 가능                            |
| 한계      | Bounding box 미포함, 객체 크기 알 수 없음                  |
| 실습 흐름 | 데이터 수집 → Impulse 설계 → 학습 → 테스트 → 디바이스 배포 |

---

## 📎 참고 링크

- [FOMO 공식 문서](https://docs.edgeimpulse.com/docs/tutorials/end-to-end-tutorials/computer-vision/object-detection/detect-objects-using-fomo)
- [Edge Impulse Studio](https://studio.edgeimpulse.com)
- [Arduino 라이브러리 배포 안내](https://docs.edgeimpulse.com/docs/edge-impulse-studio/deployment/arduino)
