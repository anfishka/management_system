document.addEventListener("DOMContentLoaded", () => {
  fetch("/products.json")
    .then((response) => response.json())
    .then((data) => {
      function createMarkup() {
        const hooks = data.products[0].classification.hooks;
        const bait =  data.products[0].classification.bait;

        const productCard = bait.map((element) => {
          return `<div class="product-card">
                <img src="${element.img}" alt="${element.name}">
                <h2>${element.name}</h2>
                <p>Price: ${element.sellingPrice}</p>
                </div> `;
        });
        const productCardHTML = productCard.join("")
        const productContainer = document.getElementById("product-container");
        productContainer.innerHTML = productCardHTML;
      }
      createMarkup();
    })
    .catch((error) => console.log("Error fetching data:", error));
});
