이번 문제는 단순하게 최대 힙을 구현하는 문제이다. 다만 요소를 제거하는 것이 단순히 제거하는 것이 아니라 제거한 값을 저장했다가 결과로 출력한다.
힙에서 중요했던 것은 문제에서도 힌트로 나왔던 부모와 자식 노드의 인덱스 관계이다.
		
  	부모 idx = 자식 idx / 2
  
	왼쪽 자식 idx = 부모 idx * 2, 오른쪽 자식 idx = 부모 idx * 2 + 1
단, 이는 idx가 1부터 시작해야 유효하다.

힙에 요소를 추가할 때는 맨 끝에 추가한 뒤 root를 향해 거슬러 올라가면서 이 숫자의 위치를 찾는다.

부모보다 크다면 부모와 바꾸고 아니라면 자식들과 비교해서 둘 중 더 큰 자식과 바꾼다.

만약 아무런 변화가 없다면 현재 위치가 이 숫자의 위치이므로 탐색을 중단한다.

<br>

힙의 요소를 제거할 때는 1번(제일 큰 수)를 제거한 뒤, 맨 마지막 수를 이 위치로 가져온다.

그리고 아래로 내려가면서 이 숫자의 위치를 찾는다.

추가와는 다르게 부모와는 비교할 필요가 없는데, root에서부터 비교하면서 왔으므로 부모는 무조건 이 수보다 크다.

따라서 자식들과 비교해서 둘 중 더 큰 자식과 바꾼다.

만약 아무런 변화가 없다면 현재 위치가 이 숫자의 위치이므로 탐색을 중단한다.


이 문제를 저번주에도 풀었는데 런타임 에러가 났다. 그 이유를 계속 찾지 못하고 헤맸는데, 이번 주에 다시 와서 문제를 다시 천천히 읽고 푸니까 쉽게 풀렸다.
그 전에는 계속 부모와 자식 둘을 한번에 비교하려고 해서 인덱스 에러가 났던 것 같다. 문제를 다시 읽고 이 부분을 명확히 하니까 쉽게 풀 수 있었다.
