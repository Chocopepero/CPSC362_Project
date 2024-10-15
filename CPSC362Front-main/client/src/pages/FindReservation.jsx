import React, { useState } from 'react';
import { FontAwesomeIcon } from '@fortawesome/react-fontawesome';
import { faSearch } from '@fortawesome/free-solid-svg-icons';
import axios from 'axios';
import { isAfter, parse } from 'date-fns';

export default function FetchReservation() {
  const [reservationID, setReservationID] = useState('');
  const [fullName, setFullName] = useState('');
  const [reservationDetails, setReservationDetails] = useState(null);
  const [error, setError] = useState('');

  const handleFetch = async (e) => {
    e.preventDefault();
    // Reset previous error and details
    setError('');
    setReservationDetails(null);

    try {
      const response = await axios.get(`/api/lookup?id=${reservationID}`);
      if (response.status === 200) {
        const reservation = JSON.parse(response.data);
        // Check if the name matches
        if (reservation._primary_guest._name.toLowerCase() === fullName.toLowerCase()) {
          const departureDate = parse(
            `${reservation._departure._year}-${reservation._departure._month}-${reservation._departure._day}`,
            'yyyy-MM-dd',
            new Date()
          );

          const fulfillmentStatus = isAfter(new Date(), departureDate);

          setReservationDetails({
            id: reservation._reservation_id,
            name: reservation._primary_guest._name,
            phone: reservation._primary_guest._phone_number,
            numOfAdults: reservation._num_of_adults,
            numOfChildren: reservation._num_of_children,
            numOfRooms: reservation._num_of_rooms,
            arrivalDate: `${reservation._arrival._month}/${reservation._arrival._day}/${reservation._arrival._year}`,
            departureDate: `${reservation._departure._month}/${reservation._departure._day}/${reservation._departure._year}`,
            fulfillmentStatus,
          });
        } else {
          setError('Name does not match with the reservation ID.');
        }
      } else {
        setError('Reservation not found. Please check your details.');
      }
    } catch (err) {
      setError('An error occurred while fetching the reservation details.');
    }
  };

  return (
    <div className="flex flex-col items-center min-h-screen bg-gradient-to-r from-blue-100 to-green-100 p-8">
      <header className="bg-blue-800 text-white p-4 text-center rounded-lg shadow-md w-full max-w-lg">
        <h1 className="text-4xl font-bold">Blissful Hotel Reservation</h1>
      </header>
      <main className="mt-8 bg-white p-8 rounded-lg shadow-lg w-full max-w-lg">
        <h2 className="text-3xl font-semibold text-gray-800 mb-6">Find Reservation Details</h2>
        <form onSubmit={handleFetch} className="space-y-6">
          <div className="flex flex-col">
            <label htmlFor="reservationID" className="text-gray-700 font-medium">Reservation ID</label>
            <input
              type="text"
              id="reservationID"
              value={reservationID}
              onChange={(e) => setReservationID(e.target.value)}
              required
              className="p-3 border rounded-lg focus:outline-none focus:ring-2 focus:ring-blue-500"
              placeholder="Enter your reservation ID"
            />
          </div>
          <div className="flex flex-col">
            <label htmlFor="fullName" className="text-gray-700 font-medium">Full Name</label>
            <input
              type="text"
              id="fullName"
              value={fullName}
              onChange={(e) => setFullName(e.target.value)}
              required
              className="p-3 border rounded-lg focus:outline-none focus:ring-2 focus:ring-blue-500"
              placeholder="Enter your full name"
            />
          </div>
          <button type="submit" className="flex items-center justify-center font-bold bg-gray-400 text-white p-3 rounded-lg hover:bg-green-700 transition duration-300 w-full">
            <FontAwesomeIcon icon={faSearch} className="mr-2" />
            Find My Reservation
          </button>
        </form>
        {error && <p className="text-red-500 mt-4">{error}</p>}
        {reservationDetails && (
          <div className="mt-6 p-4 bg-gray-100 rounded-lg shadow-inner">
            <h3 className="text-xl font-semibold text-gray-700 mb-4">Reservation Details</h3>
            <p><strong>ID:</strong> {reservationDetails.id}</p>
            <p><strong>Name:</strong> {reservationDetails.name}</p>
            <p><strong>Phone:</strong> {reservationDetails.phone}</p>
            <p><strong>Number of Adults:</strong> {reservationDetails.numOfAdults}</p>
            <p><strong>Number of Children:</strong> {reservationDetails.numOfChildren}</p>
            <p><strong>Number of Rooms:</strong> {reservationDetails.numOfRooms}</p>
            <p><strong>Arrival Date:</strong> {reservationDetails.arrivalDate}</p>
            <p><strong>Departure Date:</strong> {reservationDetails.departureDate}</p>
            <p><strong>Fulfillment Status:</strong> {reservationDetails.fulfillmentStatus ? 'Fulfilled' : 'Not Fulfilled'}</p>
          </div>
        )}
      </main>
    </div>
  );
}
