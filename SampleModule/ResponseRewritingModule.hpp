//
// Created by PC on 08/01/2017.
//

#ifndef ZIA_RESPONSE_MODULE_HH
#define ZIA_RESPONSE_MODULE_HH

#include "../Module/AModule.hpp"

namespace apouche {

    class ResponseRewritingModule : public AModule {
    public:
        ResponseRewritingModule() : AModule("ResponseRewriting",
                                            "Basic response rewriting",
                                            "1.0.0") {
        }

        ~ResponseRewritingModule() {};

        void registerEvents(EventHandler *_handler) {
            _logger.info(_name + " v" + _version + ": Event registering -> Response rewriting");

            auto function = std::bind(&ResponseRewritingModule::rewrite_response, this, std::placeholders::_1, std::placeholders::_2);
            Event<bool, HttpResponse *, IHttpConf *> _event("Response Rewriting", Weight::HIGH, function);
            _handler->_beforeSendResponse.addEvent(_event);
        };

        bool rewrite_response(HttpResponse *response, IHttpConf *conf) {
            if (conf->getConf("module.response.rewriting") == "true")
            {
                response->getBody()->setBody("Rewritten Body !");
                return true;
            }
            return false;
        };

        AModule *instantiate() const{
            return new ResponseRewritingModule();
        }
    };
    extern "C" apouche::AModule *instantiate(){
        return new ResponseRewritingModule();
    }
}

#endif //ZIA_MYMODULE_HH
