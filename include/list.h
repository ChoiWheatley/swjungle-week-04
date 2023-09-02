#pragma once
#include <mymalloc.h>
#include <stddef.h>
/**
 * C는 아직 존재하지 않는 타입에 대한 포인터 생성을 지원한다. p.160
 */
typedef struct Node* NodePtr;

/// @brief 단일연결리스트 원소를 정의.
typedef struct Node {
  int data;
  NodePtr link;
} Node;

/// @brief first 체인의 앞에 data를 가진 노드를 추가한다.
/// @param first NULLable한 타입이기 때문에 first의 주소를 인자로 받는다.
void insert_left(NodePtr* first, int data) {
  NodePtr newnode;
  MALLOC(newnode, sizeof(*newnode));
  newnode->data = data;

  if (!(*first)) {
    // first is empty, first is now data
    newnode->link = NULL;
    *first = newnode;
    return;
  }

  NodePtr oldnode = (*first)->link;
  newnode->link = oldnode;
  (*first)->link = newnode;
}

/// @brief first가 가리키고 있는 데이터를 연결해제 시킨 뒤 리턴한다.
/// @param first nullable, 연결리스트의 첫번째 원소를 가리키는 포인터.
/// @return first가 가리키고 있는 첫번째 원소 혹은 NULL을 리턴
NodePtr pop_left(NodePtr* first) {
  if (!(*first)) {
    return NULL;
  }
  NodePtr trail = (*first)->link;
  NodePtr ret = (*first);
  (*first) = trail;
  return ret;
}