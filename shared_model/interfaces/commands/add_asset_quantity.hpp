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

#ifndef IROHA_SHARED_MODEL_ADD_ASSET_QUANTITY_HPP
#define IROHA_SHARED_MODEL_ADD_ASSET_QUANTITY_HPP

#include "amount/amount.hpp"  // TODO 26/10/2017 muratovv replace with amount from shared lib
#include "interfaces/common_objects/types.hpp"
#include "interfaces/hashable.hpp"
#include "model/commands/add_asset_quantity.hpp"

namespace shared_model {
  namespace interface {

    /**
     * Add amount of asset to an account
     */
    class AddAssetQuantity
        : public Hashable<AddAssetQuantity, iroha::model::AddAssetQuantity> {
     public:
      /**
       * @return Identity of user, that add quantity
       */
      virtual const types::AccountIdType &accountId() const = 0;
      /**
       * @return asset identifier
       */
      virtual const types::AssetIdType &assetId() const = 0;
      /**
       * @return quantity of asset for adding
       */
      virtual const types::AmountType &amount() const = 0;

      std::string toString() const override {
        return detail::PrettyStringBuilder()
            .init("AddAssetQuantity")
            .append("account_id", accountId())
            .append("asset_id", assetId())
            .append("amount", amount().toString())
            .finalize();
      }

      OldModelType *makeOldModel() const override {
        auto oldModel = new iroha::model::AddAssetQuantity;
        using OldAmountType = iroha::Amount;
        /// Use shared_ptr and placement-new to copy new model field to
        /// oldModel's field and to return raw pointer
        auto p = std::shared_ptr<OldAmountType>(amount().makeOldModel());
        new (&oldModel->amount) OldAmountType(*p);
        oldModel->account_id = accountId();
        oldModel->asset_id = assetId();
        return oldModel;
      }
    };
  }  // namespace interface
}  // namespace shared_model
#endif  // IROHA_SHARED_MODEL_ADD_ASSET_QUANTITY_HPP
