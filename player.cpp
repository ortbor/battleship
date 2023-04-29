#include "player.hpp"

Player::Player(int index, int length, int width) : index_(index),
                                                   my_field_(MyField(length, width)),
                                                   rival_field_(RivalField(length, width)),
                                                   ships_(std::vector<std::vector<Ship>>(5)) {}

int Player::GetIndex() const { return index_; }

ShotResult Player::GetLastShotResult() const { return last_shot_result_; }

size_t Player::GetShipCount() const { return ship_count_; }

void Player::DecrementShipCount() { --ship_count_; }

void Player::AddShip() {
  ships_[ship_in_process_.GetSize()].push_back(ship_in_process_);
  ++ship_count_;
  my_field_.SetShip(&ship_in_process_);
}

void Player::Shoot(Cell* cell, ShotResult& shot_result) {
  rival_field_.UpdateShot(cell, shot_result);
  if (shot_result == ShotResult::Kill) {
    rival_->DecrementShipCount();
  }
  last_shot_result_ = shot_result;
}

const Ship* Player::GetShipInProcess() const { return &ship_in_process_; }

void Player::FinishSettingShip() { ship_in_process_.Clear(); }

size_t Player::GetNumberOfShipsSized(size_t size) const { return ships_[size].size(); }

void Player::LinkWithRival(Player* rival) {
  rival_ = rival;
  rival->rival_ = this;
  my_field_.LinkField(&rival->rival_field_);
  rival_field_.LinkField(&rival->my_field_);
}