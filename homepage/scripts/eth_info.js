
let price_url = "https://api.coingecko.com/api/v3/simple/price?ids=ethereum&vs_currencies=usd"




  async function getapi(url,part) {

    // Storing response
    const response = await fetch(url);

    // Storing data in form of JSON
    var data = await response.json();
    document.getElementById(part).innerHTML = data;

}
// Calling that async function
getapi(price_url);