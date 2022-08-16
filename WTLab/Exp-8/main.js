const names = document.getElementById('name');
const age = document.getElementById('age');
const department = document.getElementById('department');

const form = document.getElementById('form');

form.addEventListener('submit', (e) => {
    let messages = [];
    
    if (names.value === '' || names.value == null) {
        messages.push('Name is required');
    }

    if (parseFloat(age.value) < 1 || parseFloat(age.value) > 25 || age.value === '') {
        messages.push('Age should be between 1 and 25');
    }

    if (department.value === '' || address.value == null) {
        messages.push('Department is required');
    }
});
