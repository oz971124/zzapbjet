# [STM32] WASHING MACHINE

<aside>
💡 NUCLEO-F429ZI 개발 보드를 사용한 STM32 기반 세탁기

</aside>


### Output

---

![output.png](https://prickle-starburst-015.notion.site/image/https%3A%2F%2Fprod-files-secure.s3.us-west-2.amazonaws.com%2Fa94a1061-03b0-48eb-abdf-da844b5d915c%2F2b6761b4-726b-4912-8248-535c23018c53%2F%25EC%258A%25A4%25ED%2581%25AC%25EB%25A6%25B0%25EC%2583%25B7_2024-01-25_112821.png?table=block&id=581566fb-b038-46fc-8fad-e7ddc6e93c6b&spaceId=a94a1061-03b0-48eb-abdf-da844b5d915c&width=1070&userId=&cache=v2)


### 프로젝트 기간

---

2023.10.18 ~ 2023.10.19 (2일)


### 개발 도구

---

STM32CubeIDE


### 요구 사항

---

| 요구 사항 | 사용 모듈 | 달성 |
| --- | --- | --- |
| 동작, 일시 정지 기능이 있어야 한다 | 버튼, DCmotor | 100% |
| 세탁물 양을 파악하고 물높이를 조절해야한다 | 초음파 센서, LED BAR | 100% |
| 세탁, 헹굼, 탈수 기능이 존재하고 현재 진행 중인 기능을 나타낼 수 있어야 한다 | 3 color LED | 100% |
| 표준, 이불, 울, 스피드 세탁 모드가 존재한다 | LCD | 100% |
| 각 모드마다 기능의 정도가 정해져 있고, 사용자는 이것을 커스텀 할 수 있다 | LCD | 100% |
| 남은 시간을 나타낼 수 있어야 한다 | FND | 100% |
| 모든 동작이 완료되면 IDLE 상태가 되어야 한다 |  | 100% |
| 표준 모드 (2/2/3) / 이불 세탁 (2/3/3) / 울 세탁 (1/2/1) / 스피드 세탁 (2/1/3) | (세탁 / 헹굼 / 탈수) |  |


### 다이어그램

---

- **FSM**

![fsm.png](https://prickle-starburst-015.notion.site/image/https%3A%2F%2Fprod-files-secure.s3.us-west-2.amazonaws.com%2Fa94a1061-03b0-48eb-abdf-da844b5d915c%2Fe2a6d259-bb9a-41ce-ac43-1f7279d01571%2F%25EC%258A%25A4%25ED%2581%25AC%25EB%25A6%25B0%25EC%2583%25B7_2024-01-26_082501.png?table=block&id=eb64104b-48ff-4a9b-84c0-e41876c0581e&spaceId=a94a1061-03b0-48eb-abdf-da844b5d915c&width=1920&userId=&cache=v2)

- **클래스 다이어그램**

![class_diagram.png](https://prickle-starburst-015.notion.site/image/https%3A%2F%2Fprod-files-secure.s3.us-west-2.amazonaws.com%2Fa94a1061-03b0-48eb-abdf-da844b5d915c%2F3f88fafc-47c7-404b-81d8-fc889ccf1b2c%2F%25EC%258A%25A4%25ED%2581%25AC%25EB%25A6%25B0%25EC%2583%25B7_2024-01-26_082614.png?table=block&id=f71d318a-59e8-442a-91b0-1d0695fd042f&spaceId=a94a1061-03b0-48eb-abdf-da844b5d915c&width=1540&userId=&cache=v2)


### 시연

---

[![Video Label](http://img.youtube.com/vi/rMdcJ4L8uSU/0.jpg)](https://youtu.be/rMdcJ4L8uSU)
