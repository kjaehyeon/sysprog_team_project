# 시스템 프로그래밍 프로젝트
# EDGE RUNNER 
## 장애물과 적을 피해 화면을 따라 달리는 1인용 러닝 액션 게임
![image](https://user-images.githubusercontent.com/50866506/102114722-e6dcdb80-3e7d-11eb-9174-e2ae79bc48e8.png)

## 프로젝트 설명
### 1. 캐릭터가 콘솔창 상,하,좌,우 화면을 따라 움직이며 장애물과 적을 피해 끝까지 살아남아하는 러닝 액션 게임입니다. ### 2. 장애물은 점프 기능을 통해 장애물을 뛰어넘고 공격 기능을 통해 적을 처치할 수 있습니다. 
### 3. 오래살아 남을수록 점수가 증가하고 캐릭터가 모니터 한 바퀴를 완주함 캐릭터의 달리기 속도가 빨라져 난이도가 증가합니다. 
### 4. 게임이 끝나면 최고점수 순위를 기록해 랭킹을 매길 수 있습니다.

## 프로젝트 주요 기능
### 1. 시작화면에서 game start와 도움말 중 하나를 선택 할 수 있다.
### 2. 캐릭터가 콘솔창의 edge를 따라 달리다가 corner에 도달하면 진행방향이 90도 전환된다.
### 3. 여러 종류의 장애물이 랜덤으로 발생하며 각 장애물 마다 통과 방법이 다르다. 장애물 통과에 실패하면 게임 종료.

## 주요 코드개요
### edge_runner.c , startwin.c : 메인화면 구현 (입력에 따라 게임실행, 도움말화면을 보여줌)
### gameover.c : gameover 화면 구현 (점수표시)
### help.c : 도움말 화면 구현
### map.c : runner의 위치에 따라 map 구현
### play.c : 플레이 실행 화면 구현

## startwin.c
### main 화면을 move() , addstr()을 이용하여 표시합니다.



## 프로젝트 마일스톤
### week1(11/9 ~ 11/15) : 제안서 작성 
### week2(11/16 ~ 11/22) : 개발파트 분배 및 오브젝트 디자인
### week3(11/23 ~ 11/29) : 프로그램 구현
### week4(11/30 ~ 12/6) : 기말고사 기간
### week5(12/7 ~ 12/13) : 피드백 및 테스팅 & 발표영상 촬영