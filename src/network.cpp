#include "../lib/network.hpp"

#include "../lib/button.hpp"
#include "../lib/cell.hpp"
#include "../lib/command.hpp"
#include "../lib/game.hpp"
#include "../lib/object.hpp"
#include "../lib/player.hpp"

Network::Network(GameLoop* loop)
    : connect_thr(&Network::ServerAccept, this), loop_(loop) {
  listener_.listen(2000);
}

Socket::Status Network::UpdatePort(size_t port) {
  return listener_.listen(port);
}

void Network::Terminate() { connect_thr.terminate(); }

void Network::ServerAccept() {
  listener_.accept(socket_);
  loop_->LaunckNetwork();
  loop_->Blocked() = true;
  loop_->GetWnd().SetButtons("select_0");
}

void Network::ServerConnect() { connect_thr.launch(); }

Socket::Status Network::ClientConnect(pair<IpAddress, size_t> address) {
  return m_socket.connect(address.first, address.second, sf::milliseconds(1500));
}

void Network::ServerAccept() {
  m_listener.accept(m_socket);
  m_loop->LaunchNetwork();
  m_loop->Blocked() = true;
  m_loop->GetWnd().SetButtons("select_0");
}

<<<<<<< HEAD
<<<<<<< HEAD
||||||| 1e36bb9 (Revert "Fixed a lot of bugs, added more new ones")
void Network::ServerConnect() {
  m_connect_thr.launch();
}
||||||| 1e36bb9 (Revert "Fixed a lot of bugs, added more new ones")
void Network::ServerConnect() {
  m_connect_thr.launch();
}
=======
void Network::ServerConnect() { m_connect_thr.launch(); }
>>>>>>> parent of 1e36bb9 (Revert "Fixed a lot of bugs, added more new ones")

=======
void Network::ServerConnect() { m_connect_thr.launch(); }

>>>>>>> parent of 1e36bb9 (Revert "Fixed a lot of bugs, added more new ones")
void Network::Send(std::string command_type, std::string coords) {
  packet_.clear();
  packet_ << command_type << coords;
  if (socket_.send(packet_) == Socket::Done) {
    std::cout << "sent\n";
    std::cout.flush();
  }
}

Command* Network::GetCommand() {
  socket_.receive(packet_);
  std::string command_type;
  packet_ >> command_type;

  auto& buttons = m_loop->GetWnd().GetButtons();
  if (command_type == "add_ship") {
    return buttons.Get("select_1", "ship")->GetCommand().get();
  }

  std::string coords;
  packet_ >> coords;
  if (command_type == "add_cell") {
    return buttons.Get("select_1", "cell_m_" + coords)->GetCommand().get();
  }
  return buttons.Get("play_1", "cell_r_" + coords)->GetCommand().get();
}
