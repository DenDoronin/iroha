/**
 * Copyright Soramitsu Co., Ltd. 2017 All Rights Reserved.
 * http://soramitsu.co.jp
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *        http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef IROHA_SHARED_MODEL_CREATE_DOMAIN_HPP
#define IROHA_SHARED_MODEL_CREATE_DOMAIN_HPP

#include "interfaces/base/primitive.hpp"
#include "interfaces/common_objects/types.hpp"

#ifndef DISABLE_BACKWARD
#include "model/commands/create_domain.hpp"
#endif

namespace shared_model {
  namespace interface {
    /**
     * Create domain in Iroha
     */
    class CreateDomain : public PRIMITIVE(CreateDomain) {
     public:
      /**
       * @return Id of the domain to create
       */
      virtual const types::DomainIdType &domainId() const = 0;
      /**
       * @return default role of the user in the domain
       */
      virtual const types::RoleIdType &userDefaultRole() const = 0;

      std::string toString() const override {
        return detail::PrettyStringBuilder()
            .init("CreateDomain")
            .append("domain_id", domainId())
            .append("user_default_role", userDefaultRole())
            .finalize();
      }

#ifndef DISABLE_BACKWARD
      OldModelType *makeOldModel() const override {
        auto oldModel = new iroha::model::CreateDomain;
        oldModel->domain_id = domainId();
        oldModel->user_default_role = userDefaultRole();
        return oldModel;
      }
#endif

      bool operator==(const ModelType &rhs) const override {
        return domainId() == rhs.domainId()
            and userDefaultRole() == rhs.userDefaultRole();
      }
    };
  }  // namespace interface
}  // namespace shared_model

#endif  // IROHA_SHARED_MODEL_CREATE_DOMAIN_HPP
