# 2020학년도 2학기 시스템 프로그래밍 프로젝트
## EDGE RUNNER 
### 장애물과 적을 피해 화면을 따라 달리는 1인용 러닝 액션 게임
![image](https://user-images.githubusercontent.com/50866506/102114722-e6dcdb80-3e7d-11eb-9174-e2ae79bc48e8.png)

#### 플레이 영상(https://www.youtube.com/watch?v=4U3u7OBPJJA&feature=youtu.be)


## 프로젝트 설명
### 1. 캐릭터가 콘솔창 상,하,좌,우 화면을 따라 움직이며 장애물과 적을 피해 끝까지 살아남아하는 러닝 액션 게임입니다.
### 2. 장애물은 점프 기능을 통해 장애물을 뛰어넘고 공격 기능을 통해 적을 처치할 수 있습니다. 
### 3. 오래살아 남을수록 점수가 증가하고 캐릭터가 모니터 한 바퀴를 완주함 캐릭터의 달리기 속도가 빨라져 난이도가 증가합니다. 
### 4. 게임이 끝나면 최고점수 순위를 기록해 랭킹을 매길 수 있습니다.


## 프로젝트 주요 기능
### 1. 시작화면에서 game start와 도움말 중 하나를 선택 할 수 있다.
### 2. 캐릭터가 콘솔창의 edge를 따라 달리다가 corner에 도달하면 진행방향이 90도 전환된다.
### 3. 여러 종류의 장애물이 랜덤으로 발생하며 각 장애물 마다 통과 방법이 다르다. 장애물 통과에 실패하면 게임 종료.

## 주요 코드개요
### startwin.c
#### main 화면을 move() , addstr()을 이용하여 표시합니다.

### edge_runner.c
#### - main funciton이 있는 파일
#### - cur_state는 현재 프로그램의 상태를 나타낸다
#### - startwin() 함수로 시작화면을 먼저 보여주며 while문 내부에서 키 입력을 받아 입력값에 알맞는 화면과 상태로 전환한다

### map.c
#### - 상하좌우 map을 배열형태로 생성 몬스터, 나무, 허들을 랜덤으로 배열map에 저장하여 표시합니다.
#### - player position에 따라 map을 update합니다.

### play.c - set_ticker()
#### - setitimer() 시스템콜을 이용하여 주기적으로 SIGALRM을 발생시키고 이를 handling하여 runner의 움직임을 구현하고, 장애물의 통과 여부를 실시간으로 체크

### play.c - play() 
#### - signal 함수로 시그널이 발생하면 handler로 처리합니다.
#### - 유저입력을 받아 runner의 상태를 변경하고 ‘spacebar’를 누르면 jump, ‘a’를 누르면 공격, ‘s’를 누르면 슬라이딩을 구현합니다.

### play.c - draw_runner()
#### - score을 증가시켜 점수를 표시
#### - runner의 action 상태를 파악하여 run, attack, slide, 함수를 불러서 실행합니다.
#### - mvaddchr() 함수를 사용합니다.

### play.c - handler()
#### -SIGALRM에 의해 주기적으로(0.05s) 실행됩니다.
#### -draw_runner()에서 각 action에 알맞은 형태의 캐릭터를 출력하고, 화면에 주기적으로 출력함으로써 위치를 업데이트 합니다.
#### -checking()에서는 캐릭터가 각 장애물에서 알맞은 action을 실행하고 있는지 검사하고 pass/fail을 판단합니다. fail일 경우 gameover화면으로 넘어갑니다.

### play.c – checking()
#### 1. runner->pos가 어딘지 판단합니다.
#### 2. Runner가 어떤 장애물을 만났는지  판단합니다.
#### 3. 몬스터(case 1)와 허들(case 2)을 만난 경우는 runner->act가 각각Attack, slide가 아닐 경우 gameover()함수를 호출 합니다.
#### 4. 나무(case 2)를 만난 경우 runner의 현재 위치와 나무의 현재 위치가 겹치면 gameover()함수를 호출합니다.

## makefile
![image](https://user-images.githubusercontent.com/50866506/102115663-353eaa00-3e7f-11eb-9679-1450bf7fbaa2.png)



# 프로젝트 마일스톤
### week1(11/9 ~ 11/15) : 제안서 작성 
### week2(11/16 ~ 11/22) : 개발파트 분배 및 오브젝트 디자인
### week3(11/23 ~ 11/29) : 프로그램 구현
### week4(11/30 ~ 12/6) : 기말고사 기간
### week5(12/7 ~ 12/13) : 피드백 및 테스팅 & 발표영상 촬영
