#pragma once

#include "common.hpp"
#include "field.hpp"
#include "ship.hpp"

class Player {
  friend AddCellToShipCommand;

 public:
  Player(size_t index, const Vector2f& size);
  ~Player() = default;

  size_t GetIndex() const;
  ShotResult GetLastShotResult() const;
  size_t GetShipCount() const;
  Field* GetField();
  void DecrementShipCount();
  void AddShip();
  void Shoot(Cell* cell, ShotResult& shot_result);
  const Ship* GetShipInProcess() const;
  void FinishSettingShip();
  size_t GetNumberOfShipsSized(size_t size) const;
  void LinkWithRival(Player* rival);

 protected:
  size_t index_;
  ShotResult last_shot_result_;
  size_t ship_count_;
  MyField my_field_;
  RivalField rival_field_;
  vector<vector<Ship>> ships_;
  Ship ship_in_process_;
  Player* rival_;
};