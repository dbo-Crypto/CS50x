
function enterSound(){

  const audio = new Audio("./sound/door.mp3");
  audio.play();
  setTimeout(link, 1700);

  function link(){
    window.location.href = "./menu.html";
  }
}
