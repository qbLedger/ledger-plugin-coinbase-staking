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

const contractAddr = '0x858646372cc42e1a627fce94aa7a7033e7cf075a';

const pluginName = 'Kiln';
const abi_path = `../cal/abis/${contractAddr}.json`;
const abi = require(abi_path);

nano_models.forEach(function (model) {
  test(
    '[Nano ' + model.letter + '] Deposit Into Strategy ',
    zemu(model, async (sim, eth) => {
      const contract = new ethers.Contract(contractAddr, abi);

      const { data } = await contract.populateTransaction.depositIntoStrategy(
        '0x0Fe4F44beE93503346A3Ac9EE5A26b130a5796d6',
        '0x1e68238ce926dec62b3fbc99ab06eb1d85ce0270',
        42
      );

      let unsignedTx = genericTx;

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
      const right_clicks = 6;

      await waitForAppScreen(sim);
      await sim.navigateAndCompareSnapshots(
        '.',
        model.name + '_depositIntoStrategy',
        [right_clicks, 0]
      );
      await tx;
    }),
    30000
  );
});
