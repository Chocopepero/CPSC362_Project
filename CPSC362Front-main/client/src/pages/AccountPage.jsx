import React, { useContext, useEffect, useState } from 'react';
import axios from 'axios';
import AuthContext  from '../assets/components/Authenticate';
import { MDBInput, MDBBtn } from 'mdb-react-ui-kit';

export default function AccountPage() {
  const { user } = useContext(AuthContext);
  const [userDetails, setUserDetails] = useState(null);
  const [newUsername, setNewUsername] = useState('');
  const [newEmail, setNewEmail] = useState('');
  const [newPassword, setNewPassword] = useState('');
  const [reservationId, setReservationId] = useState('');

  useEffect(() => {
    if (user) {
      axios.get('/api/user')
        .then(response => {
          setUserDetails(response.data);
        })
        .catch(error => {
          console.error('Error fetching user details:', error);
        });
    }
  }, [user]);

  const handleUpdateUsername = () => {
    axios.post('/api/update-username', { username: newUsername })
      .then(response => {
        alert('Username updated successfully');
        setUserDetails({ ...userDetails, username: newUsername });
      })
      .catch(error => {
        console.error('Error updating username:', error);
      });
  };

  const handleUpdateEmail = () => {
    axios.post('/api/update-email', { email: newEmail })
      .then(response => {
        alert('Email updated successfully');
        setUserDetails({ ...userDetails, email: newEmail });
      })
      .catch(error => {
        console.error('Error updating email:', error);
      });
  };

  const handleUpdatePassword = () => {
    axios.post('/api/update-password', { password: newPassword })
      .then(response => {
        alert('Password updated successfully');
      })
      .catch(error => {
        console.error('Error updating password:', error);
      });
  };

  const handleCancelReservation = () => {
    axios.post('/api/cancel-reservation', { reservationId })
      .then(response => {
        alert('Reservation cancelled successfully');
        setUserDetails({
          ...userDetails,
          reservations: userDetails.reservations.filter(id => id !== parseInt(reservationId))
        });
      })
      .catch(error => {
        console.error('Error cancelling reservation:', error);
      });
  };

  if (!user) {
    return <div>Please log in to view your account details.</div>;
  }

  if (!userDetails) {
    return <div>Loading...</div>;
  }

  return (
    <div className="p-4 flex-col">
      <div className="container mx-auto p-8">
        <div className="max-w-md mx-auto bg-white border border-gray-200 rounded-lg shadow-lg">
          <div className="p-6">
            <h2 className="text-2xl font-bold mb-4">Account Page</h2>
            <div>
              <h3 className="text-xl font-semibold">Contact Information</h3>
              <p>Name: {userDetails.contact_info.name}</p>
              <p>Phone: {userDetails.contact_info.phone_number}</p>
            </div>
            <div className="mb-4">
              <h3 className="text-xl font-semibold">Username</h3>
              <p>{userDetails.username}</p>
              <MDBInput label="New Username" value={newUsername} onChange={(e) => setNewUsername(e.target.value)} />
              <MDBBtn onClick={handleUpdateUsername} className="mt-2">Update Username</MDBBtn>
            </div>
            <div className="mb-4">
              <h3 className="text-xl font-semibold">Email</h3>
              <p>{userDetails.email}</p>
              <MDBInput label="New Email" value={newEmail} onChange={(e) => setNewEmail(e.target.value)} />
              <MDBBtn onClick={handleUpdateEmail} className="mt-2">Update Email</MDBBtn>
            </div>
            <div className="mb-4">
              <h3 className="text-xl font-semibold">Change Password</h3>
              <MDBInput label="New Password" type="password" value={newPassword} onChange={(e) => setNewPassword(e.target.value)} />
              <MDBBtn onClick={handleUpdatePassword} className="mt-2">Update Password</MDBBtn>
            </div>
            <div>
              <h3 className="text-xl font-semibold">Reservations</h3>
              <ul>
                {userDetails.reservations.map(id => (
                  <li key={id}>Reservation ID: {id}</li>
                ))}
              </ul>
              <MDBInput label="Reservation ID to Cancel" value={reservationId} onChange={(e) => setReservationId(e.target.value)} />
              <MDBBtn onClick={handleCancelReservation} className="mt-2">Cancel Reservation</MDBBtn>
            </div>
          </div>
        </div>
      </div>
    </div>
  );
}
