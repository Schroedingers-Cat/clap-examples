#pragma once

#include <clap/clap.h>

namespace clap {

   class CorePlugin;
   class AbstractGuiListener;
   class AbstractGui {
   public:
      AbstractGui(AbstractGuiListener &listener);
      virtual ~AbstractGui();

      virtual void defineParameter(const clap_param_info &paramInfo) = 0;
      virtual void updateParameter(clap_id paramId, double value, double modAmount) = 0;

      virtual void clearTransport() = 0;
      virtual void updateTransport(const clap_event_transport &transport) = 0;

      virtual bool attachCocoa(void *nsView) = 0;
      virtual bool attachWin32(clap_hwnd window) = 0;
      virtual bool attachX11(const char *displayName, unsigned long window) = 0;

      virtual bool size(uint32_t *width, uint32_t *height) = 0;
      virtual bool setScale(double scale) = 0;

      virtual bool show() = 0;
      virtual bool hide() = 0;

      virtual void destroy() = 0;

   protected:
      AbstractGuiListener &_listener;

      bool _isTransportSubscribed = false;
   };

} // namespace clap