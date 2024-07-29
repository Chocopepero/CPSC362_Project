document.addEventListener('DOMContentLoaded', () => {
    const createUserForm = document.getElementById('createUser');
    const createMessageDiv = document.getElementById('createMessage');
    const loginForm = document.getElementById('loginForm');
    const loginMessageDiv = document.getElementById('loginMessage');
    const reservationReq = document.getElementById('reserveReq');
    const reservationReqMessage = document.getElementById('reserveReqMessage');
    const lookupForm = document.getElementById('lookupReq');
    const reservationInfoDiv = document.getElementById('reserveLookup');

    createUserForm.addEventListener('submit', (event) => {
        event.preventDefault(); // Prevent form from submitting the default way

        const username = document.getElementById('usernameCreate').value;
        const password = document.getElementById('passwordCreate').value;
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

        fetch('http://localhost:18080/api/create', {
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
            createMessageDiv.textContent = 'User creation successful!';
            createMessageDiv.style.color = 'green';
        })
        .catch(error => {
            createMessageDiv.textContent = 'User creation failed: ' + error.message;
            createMessageDiv.style.color = 'red';
        });
    });

    loginForm.addEventListener('submit', (event) => {
        event.preventDefault(); // Prevent form from submitting the default way

        const username = document.getElementById('usernameLogin').value;
        const password = document.getElementById('passwordLogin').value;

        const formData = {
            username,
            password
        };

        fetch('http://localhost:18080/api/login', {
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
            loginMessageDiv.textContent = 'Login successful!';
            loginMessageDiv.style.color = 'green';
        })
        .catch(error => {
            loginMessageDiv.textContent = 'Login failed: ' + error.message;
            loginMessageDiv.style.color = 'red';
        });
    });

  reservationReq.addEventListener('submit', (event) => {
    event.preventDefault();

    const room = document.getElementById('room').value;
    const numberOfRooms = document.getElementById('numberOfRooms').value;
    const startDateIn = document.getElementById('startDate').value;
    const startDate = new Date(startDateIn);
    const startYear = startDate.getFullYear();
    const startMonth = startDate.getMonth() + 1;
    const startDay = startDate.getDate() + 1;
    const endDateIn = document.getElementById('endDate').value;
    const endDate = new Date(endDateIn);
    const endYear = endDate.getFullYear();
    const endMonth = endDate.getMonth() + 1;
    const endDay = endDate.getDate() + 1;
    const adult = document.getElementById('adult').value;
    const child = document.getElementById('child').value;
    const name = document.getElementById('name').value;
    const phone = document.getElementById('phone').value;

    const formData = {
      room,
      numberOfRooms,
      startYear,
      startMonth,
      startDay,
      endYear,
      endMonth,
      endDay,
      adult,
      child,
      name,
      phone
    };

    fetch('http://localhost:18080/api/reserve', {
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
        console.log(data);
        const reservationData = JSON.parse(data);
        reservationReqMessage.innerHTML = `
                    <p><strong>Message:</strong> ${reservationData.message}</p>
                    <p><strong>Reservation ID:</strong> ${reservationData.reservation_id}</p>
                `;
        reservationReqMessage.style.color = 'green';
      })
      .catch(error => {
        reservationReqMessage.textContent = 'Reservation failed: ' + error.message;
        reservationReqMessage.style.color = 'red';
      });
  });
    lookupForm.addEventListener('submit', (event) => {
        event.preventDefault(); // Prevent form from submitting the default way

        const reservationId = document.getElementById('lookup').value;
        if (!reservationId) {
            alert("Please enter a reservation ID");
            return;
        }
        fetchReservation(reservationId);
    });

    function fetchReservation(reservationId) {
        fetch(`http://localhost:18080/api/lookup?id=${reservationId}`)
            .then(response => {
                if (!response.ok) {
                    throw new Error('Network response was not ok');
                }
                return response.json();
            })
            .then(data => {
                displayReservation(data,reservationId);
            })
            .catch(error => {
                console.error('There has been a problem with your fetch operation:', error);
                reservationInfoDiv.textContent = 'Error fetching reservation: ' + error.message;
            });
    }

    function displayReservation(data,id) {
        reservationInfoDiv.innerHTML = `
            <h2>Reservation ID: ${id}</h2>
            <p><strong>Primary Guest:</strong> ${data._primary_guest._name} (${data._primary_guest._phone_number})</p>
            <p><strong>Number of Adults:</strong> ${data._num_of_adults}</p>
            <p><strong>Number of Children:</strong> ${data._num_of_children}</p>
            <p><strong>Number of Rooms:</strong> ${data._num_of_rooms}</p>
            <p><strong>Arrival Date:</strong> ${data._arrival._month}/${data._arrival._day}/${data._arrival._year}</p>
            <p><strong>Departure Date:</strong> ${data._departure._month}/${data._departure._day}/${data._departure._year}</p>
            <p><strong>Bed Types:</strong></p>
            <ul>
                ${data._bed_types.map(bed => `<li>${bed.Type}: ${bed.Num}</li>`).join('')}
            </ul>
            <p><strong>Fulfillment Status:</strong> ${data._fulfillment_status ? 'Fulfilled' : 'Not Fulfilled'}</p>
        `;
    }
});
