<main>
  <slot />
</main>

<style global lang="scss">
  @import "bulma/bulma.sass";
  * {
    user-select: none;
  }
  input {
    user-select: initial;
  }

  main {
    position: relative;
    max-width: 56em;
    background-color: white;
    padding: 2em;
    margin: 0 auto;
    box-sizing: border-box;
  }
</style>
