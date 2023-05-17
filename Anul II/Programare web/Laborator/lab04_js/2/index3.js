function validateForm() {
    var nameInput = document.getElementById("name");
    var birthdateInput = document.getElementById("birthdate");
    var ageInput = document.getElementById("age");
    var emailInput = document.getElementById("email");

    var isValid = true;

    if (nameInput.value === "") {
        isValid = false;
        nameInput.classList.add("error");
    } else {
        nameInput.classList.remove("error");
    }

    if (birthdateInput.value === "") {
        isValid = false;
        birthdateInput.classList.add("error");
    } else {
        birthdateInput.classList.remove("error");
    }

    if (ageInput.value === "" || isNaN(ageInput.value)) {
        isValid = false;
        ageInput.classList.add("error");
    } else {
        ageInput.classList.remove("error");
    }

    if (emailInput.value === "") {
        isValid = false;
        emailInput.classList.add("error");
    } else {
        emailInput.classList.remove("error");
    }

    if (isValid) {
        alert("Datele sunt completate corect");
    } else {
        alert("Unele campuri nu sunt completate corect");
    }
}
