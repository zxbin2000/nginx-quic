
/*
 * Copyright (C) sunlei
 */

#ifndef QUICHE_QUIC_QUIC_NGX_DISPATCHER_H_
#define QUICHE_QUIC_QUIC_NGX_DISPATCHER_H_

#include "net/third_party/quiche/src/quic/tools/quic_simple_dispatcher.h"

namespace quic {

class QuicNgxDispatcher : public QuicSimpleDispatcher {
 public:
  QuicNgxDispatcher(
      const QuicConfig* config,
      const QuicCryptoServerConfig* crypto_config,
      QuicVersionManager* version_manager,
      std::unique_ptr<QuicConnectionHelperInterface> helper,
      std::unique_ptr<QuicCryptoServerStream::Helper> session_helper,
      std::unique_ptr<QuicAlarmFactory> alarm_factory,
      QuicSimpleServerBackend* quic_simple_server_backend,
      uint8_t expected_connection_id_length);

  ~QuicNgxDispatcher() override;

  // QuicSession::Visitor interface implementation (via inheritance of
  // QuicTimeWaitListManager::Visitor):
  // Queues the blocked writer for later resumption.
  void OnWriteBlocked(QuicBlockedWriterInterface* blocked_writer) override;

 protected:
  std::unique_ptr<QuicSession> CreateQuicSession(
      QuicConnectionId connection_id,
      const QuicSocketAddress& client_address,
      quiche::QuicheStringPiece alpn,
      const ParsedQuicVersion& version) override;

};

}  // namespace quic

#endif  // QUICHE_QUIC_QUIC_NGX_DISPATCHER_H_
