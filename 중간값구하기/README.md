처음에 숫자 하나를 주고, N번에 걸쳐서 두 개의 수를 계속 주는데, 매번 지금까지 받은 수들 중 중간값을 누적해서 더해야 한다.

<br>
이를 maxheap, minheap을 이용해 구해야하는데 이를 보고 바로 다음과 같은 구조를 생각했다.
<br>

            maxheap                                minheap
    -------------------------             -------------------------
    |    mid보다 작은 값들          mid     mid보다 크거나 같은 값들 |
    -------------------------             -------------------------

<br>
두 수 a, b를 받고 이들을 위 max heap과  min heap에 각각 넣는다.
그러면 경우의 수는 세 가지이다.
<br>
    
    (수를 넣기 전, 균형을 이룬 상태에서 heap의 원소 수를 n개라고 하자.)
<br>

    
    1. a, b 모두 mid보다 작은 경우:
    maxheap은 n + 2개, minheap은 n개 있으므로 mid를 minheap에 넣고 maxheap의 top이 새로운 mid가 된다.
<br>
    
    2. a는 mid보다 작고 b는 mid보다 크거나 같은 경우:
    
    두 heap이 균형을 이루므로 mid는 변하지 않는다.
<br> 

    3. a, b 모두 mid보다 크거나 같은 경우:
    
    maxheap은 n개, minheap은 n + 2개 있으므로 mid를 maxheap에 넣고 minheap의 top이 새로운 mid가 된다.
