#include "../lib/player.hpp"

#include "../lib/cell.hpp"

Player::Player(size_t index, const Vector2f& size)
    : index_(index),
      last_shot_result_(ShotResult::Unknown),
      ship_count_(0),
      my_field_(MyField(size)),
      rival_field_(RivalField(size)),
      ships_(vector<vector<Ship>>(5)),
      rival_(nullptr) {}

size_t Player::GetIndex() const { return index_; }

ShotResult Player::GetLastShotResult() const { return last_shot_result_; }

size_t Player::GetShipCount() const { return ship_count_; }

/*Field* Player::GetField() { return dynamic_cast<Field*>(&my_field_); }

Field* Player::GetRField() { return dynamic_cast<Field*>(&rival_field_); }*/

MyField* Player::GetField() { return &my_field_; }

RivalField* Player::GetRField() { return &rival_field_; }

void Player::DecrementShipCount() { --ship_count_; }

void Player::AddShip() {
  ships_[ship_in_process_.GetSize()].push_back(ship_in_process_);
  ++ship_count_;
  my_field_.SetShip(&*ships_[ship_in_process_.GetSize()].rbegin());
  ship_in_process_.Clear();
}

void Player::Shoot(Cell* cell, ShotResult& shot_result) {
  RivalField::UpdateShot(cell, shot_result);
  if (shot_result == ShotResult::Kill) {
    rival_->DecrementShipCount();
  }
  last_shot_result_ = shot_result;
}

const Ship* Player::GetShipInProcess() const { return &ship_in_process_; }

size_t Player::GetNumberOfShipsSized(size_t size) const {
  return ships_[size].size();
}

void Player::LinkWithRival(Player* rival) {
  rival_ = rival;
  rival->rival_ = this;
  my_field_.LinkField(&rival->rival_field_);
  rival_field_.LinkField(&rival->my_field_);
}

Player* Player::GetRival() { return rival_; }
