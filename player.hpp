#pragma once

#include "common.hpp"
#include "field.hpp"

class Player {
  friend class AddCellToShipCommand;

 public:
  Player(int index, int length, int width);
  ~Player() = default;

  int GetIndex() const;
  ShotResult GetLastShotResult() const;
  size_t GetShipCount() const;
  void DecrementShipCount();
  void AddShip();
  void Shoot(Cell* cell, ShotResult& shot_result);
  const Ship* GetShipInProcess() const;
  void FinishSettingShip();
  size_t GetNumberOfShipsSized(size_t size) const;
  void LinkWithRival(Player* rival);

 protected:
  int index_;
  ShotResult last_shot_result_;
  size_t ship_count_;
  MyField my_field_;
  RivalField rival_field_;
  std::vector<std::vector<Ship>> ships_;
  Ship ship_in_process_;
  Player* rival_;
};