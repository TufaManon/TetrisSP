//
// Created by Tufa Manon on 2023/1/26.
//

#ifndef TETRIS_LOOP_NODE_H_
#define TETRIS_LOOP_NODE_H_
#include <cinttypes>

class LoopNode {
 public:
  virtual ~LoopNode() = default;
  virtual void Update(uint64_t delta) = 0;
};

#endif//TETRIS_LOOP_NODE_H_
