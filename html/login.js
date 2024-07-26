document.addEventListener('DOMContentLoaded', () => {
  const loginForm = document.getElementById('loginForm');
  const messageDiv = document.getElementById('message');

  loginForm.addEventListener('submit', (event) => {
    event.preventDefault(); // Prevent form from submitting the default way

    const username = document.getElementById('username').value;
    const password = document.getElementById('password').value;
    const email = document.getElementById('email').value;
    const name = document.getElementById('fullName').value;
    const phone_num = document.getElementById('phoneNumber').value;

    const formData = {
      username,
      password,
      email,
      name,
      phone_num
    };

    fetch('http://localhost:18080/create', {
      method: 'POST',
      headers: {
        'Content-Type': 'application/json'
      },
      body: JSON.stringify(formData)
    })
      .then(response => {
        if (!response.ok) {
          throw new Error('Network response was not ok');
        }
        return response.text();
      })
      .then(data => {
        // Handle the response data (e.g., show a success message or redirect)
        messageDiv.textContent = 'Submission successful!';
        messageDiv.style.color = 'green';
        // Optionally redirect or handle the successful submission here
      })
      .catch(error => {
        // Handle any errors (e.g., show an error message)
        messageDiv.textContent = 'Submission failed: ' + error.message;
        messageDiv.style.color = 'red';
      });
  });
});
