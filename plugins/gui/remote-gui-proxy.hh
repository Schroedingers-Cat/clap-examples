#pragma once

#include "../io/remote-channel.hh"

#include "abstract-gui.hh"

namespace clap {
   class RemoteGuiFactoryProxy;
   class RemoteGuiProxy : public AbstractGui {
   public:
      RemoteGuiProxy(RemoteGuiFactoryProxy &factory, uint32_t clientId);

      void defineParameter(const clap_param_info &paramInfo) override;
      void updateParameter(clap_id paramId, double value, double modAmount) override;

      void clearTransport() override;
      void updateTransport(const clap_event_transport &transport) override;

      bool attachCocoa(void *nsView) override;
      bool attachWin32(clap_hwnd window) override;
      bool attachX11(const char *displayName, unsigned long window) override;

      bool size(uint32_t *width, uint32_t *height) override;
      bool setScale(double scale) override;

      bool show() override;
      bool hide() override;

      void destroy() override;

   private:
      friend class RemoteGuiFactoryProxy;

      void onMessage(const RemoteChannel::Message &msg);

      RemoteGuiFactoryProxy &_clientFactory;
      const uint32_t _clientId;
   };
} // namespace clap