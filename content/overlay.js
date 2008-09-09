var bonjourfoxy = {
  onLoad: function() {
    // initialization code
    this.initialized = true;
    this.strings = document.getElementById("bonjourfoxy-strings");
  },
  onMenuItemCommand: function(e) {
    toggleSidebar("viewBonjourServices");
  },
  onToolbarButtonCommand: function(e) {
    // just reuse the function above
    bonjourfoxy.onMenuItemCommand(e);
  }

};
window.addEventListener("load", function(e) { bonjourfoxy.onLoad(e); }, false);
