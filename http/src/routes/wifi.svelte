<script>
  let showPasswordAsText = false;
  let useStatic = false;

  let isSubmitting = false;

  let networkConfig =  {
    ssid: '',
    password: '',
  }

  let staticIP = ""
  let staticMask = ""

  import { eyeOffOutline, eye } from "ionicons/icons/index";
  import "bulma-checkradio";

  import IPAddressMask from "../components/IPAddressMask";

  function doSave() {
    isSubmitting = true;
    
    let ipData = {
      mode: 'dhcp' // Default
    }

    if (useStatic) {
      ipData = {
        mode: 'static',
        staticConfig: {
          ip: staticIP,
          mask: staticMask,
        }
      }
    }


    fetch("", {
      method: "POST",
      headers: {
        'Content-Type': 'application/json'
      },
      body: JSON.stringify({
        networkConfig, ...ipData

      })
    })
  }
</script>

<ul id="networksList" />

<form>
  <div class="field">
    <label class="label">SSID</label>
    <div class="control">
      <input class="input" name="ssid" type="text" placeholder="Enter SSID" />
    </div>
  </div>

  <div class="field">
    <label class="label">Password</label>
    <div class="field has-addons">
      <div class="control" style="flex: 1">
        <input
          name="password"
          width="100%"
          class="input"
          type={showPasswordAsText ? "text" : "password"}
          placeholder="Enter password"
        />
      </div>
      <div class="control">
        <a
          on:click={() => (showPasswordAsText = !showPasswordAsText)}
          class="button is-info"
        >
          <span class="icon">
            <img src={showPasswordAsText ? eye : eyeOffOutline} />
          </span>
        </a>
      </div>
    </div>
  </div>
</form>

<form on:submit|preventDefault>
  <div class="field">
    <label class="label">Select IP Configuration</label>
    <div class="field">
      <input
        class="is-checkradio is-info"
        id="IPuseDHCP"
        type="radio"
        name="exampleRadioInline"
        checked={!useStatic}
        on:change={() => (useStatic = false)}
      />
      <label for="IPuseDHCP">DHCP</label>
      <input
        class="is-checkradio is-info"
        id="IPuseStatic"
        type="radio"
        name="IPuseDHCPorStatic"
        checked={useStatic}
        on:change={() => (useStatic = true)}
      />
      <label for="IPuseStatic">Static</label>
    </div>
  </div>

  <div>
    <div class="field">
      <label class="label">IP Address</label>
      <div class="control">
        <input
          class="input"
          name="ssid"
          type="text"
          use:IPAddressMask
          disabled={!useStatic}
          bind:value={staticIP}
          placeholder="Enter IP Address as xxx.xxx.xxx.xxx"
        />
      </div>
    </div>
    <div class="field">
      <label class="label">Subnet</label>
      <div class="control">
        <input
          class="input"
          name="ssid"
          type="text"
          use:IPAddressMask
          disabled={!useStatic}
          bind:value={staticMask}
          placeholder="Enter subnet mask as xxx.xxx.xxx.xxx"
        />
      </div>
    </div>
  </div>

  <div class="field">
    <div class="field-label" />
    <div class="control">
      <button on:click={doSave} class="button is-info" class:is-loading={isSubmitting}>Submit</button>
    </div>
  </div>
</form>

<style lang="scss">
  form {
    margin: 0 auto;

    &:not(:last-child) {
      margin-bottom: 50px;
    }
  }
</style>
