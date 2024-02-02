import 'core-js/stable';
import 'regenerator-runtime/runtime';
import {
  waitForAppScreen,
  kilnJSON,
  zemu,
  genericTx,
  nano_models,
  SPECULOS_ADDRESS,
  txFromEtherscan,
} from './test.fixture';
import { ethers } from 'ethers';
import { parseEther, parseUnits } from 'ethers/lib/utils';
import { ledgerService } from '@ledgerhq/hw-app-eth';

const contractAddr = '0x858646372cc42e1a627fce94aa7a7033e7cf075a'; // strategy manager

const pluginName = 'Kiln';
const abi_path = `../cal/abis/${contractAddr}.json`;
const abi = require(abi_path);

nano_models.forEach(function (model) {
  test(
    '[Nano ' + model.letter + '] Stake Eth',
    zemu(model, async (sim, eth) => {
      const contract = new ethers.Contract(contractAddr, abi);

      const queuedWithdrawal = {
        strategies: [
          '0x13760F50a9d7377e4F20CB8CF9e4c26586c658ff', // ankrETH strat
          '0xa4C637e0F704745D182e4D38cAb7E7485321d059', // OETH strat
        ],
        shares: [1000, 2000],
        depositor: '0xd8dA6BF26964aF9D7eEd9e03E53415D37aA96045',
        withdrawerAndNonce: {
          withdrawer: '0xd8dA6BF26964aF9D7eEd9e03E53415D37aA96045',
          nonce: 1,
        },
        withdrawalStartBlock: 12345678,
        delegatedAddress: '0xd8dA6BF26964aF9D7eEd9e03E53415D37aA96045', // Placeholder delegated address
      };
      const tokens = [
        '0xE95A203B1a91a908F9B9CE46459d101078c2c3cb', // ankrETH erc20
        '0x856c4Efb76C1D1AE02e20CEB03A2A6a08b0b8dC3', // OETH erc20
      ]; // Placeholder token addresses
      const middlewareTimesIndex = 0; // Placeholder middleware times index
      const receiveAsTokens = true; // Placeholder boolean

      // Generate the transaction data 0xf044c946
      const { data } =
        await contract.populateTransaction.completeQueuedWithdrawal(
          queuedWithdrawal,
          tokens,
          middlewareTimesIndex,
          receiveAsTokens
        );

      let unsignedTx = genericTx;
      console.log(unsignedTx);

      unsignedTx.to = contractAddr;
      unsignedTx.data = data;
      unsignedTx.value = parseEther('0');

      const serializedTx = ethers.utils
        .serializeTransaction(unsignedTx)
        .slice(2);
      const resolution = await ledgerService.resolveTransaction(
        serializedTx,
        eth.loadConfig,
        {
          externalPlugins: true,
        }
      );
      const tx = eth.signTransaction("44'/60'/0'/0", serializedTx, resolution);
      const right_clicks = 4;

      await waitForAppScreen(sim);
      await sim.navigateAndCompareSnapshots(
        '.',
        model.name + '_lrCompleteQueuedWithdrawal',
        [right_clicks, 0]
      );
      await tx;
    }),
    30000
  );
});
