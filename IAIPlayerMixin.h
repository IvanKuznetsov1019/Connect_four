#ifndef I_AI_PLAYER_MIXIN_H
#define I_AI_PLAYER_MIXIN_H

class IAIPlayerMixin {
 public:
  virtual int getDifficultyLevel() const = 0;
  virtual void setDifficultyLevel(int level) = 0;

 protected:
  int difficultyLevel = 1;
};
#endif