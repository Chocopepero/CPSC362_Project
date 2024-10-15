import React, { useState } from 'react';
import { format } from "date-fns";
import { useLocation, useNavigate } from 'react-router-dom';
import axios from 'axios';
import { MDBInput, MDBBtn } from 'mdb-react-ui-kit';
import img1 from "../images/Hotelpic1.jpeg";
import img2 from "../images/DeluxeRoom.webp";
import img3 from "../images/Hotelpic3.webp";

// Sample room data for demonstration
const rooms = [
    {
        id: 1,
        name: 'Deluxe Room',
        description: 'A spacious room with a beautiful view of the city.',
        price: 200, // price as a number
        imageUrl: img2,
        link: '/DeluxeRoom'
    },
    {
        id: 2,
        name: 'Standard Room',
        description: 'A comfortable room with all the basic amenities.',
        price: 100, // price as a number
        imageUrl: img1,
        link: '/StandardRoom'
    },
    {
        id: 3,
        name: 'Suite',
        description: 'A luxurious suite with a separate living area.',
        price: 300, // price as a number
        imageUrl: img3,
        link: '/SuiteRoom'
    }
];

export default function Confirmation() {
    const { state } = useLocation();
    const navigate = useNavigate();
    const { RoomType, date, searchPref } = state;

    const [name, setName] = useState('');
    const [phone, setPhone] = useState('');

    // Find the room details based on the selected RoomType
    const selectedRoom = rooms.find(room => room.name === RoomType);

    // Calculate the total cost
    const nights = Math.ceil((date[0].endDate - date[0].startDate) / (1000 * 60 * 60 * 24));
    const totalCost = selectedRoom ? selectedRoom.price * searchPref.room * nights : 0;

    const handleConfirmBooking = async () => {
        const reservationData = {
            name: name,
            phone: phone,
            numAdults: searchPref.adult,
            numChildren: searchPref.children,
            numberRooms: searchPref.room,
            roomType: RoomType,
            arrivalDate: format(date[0].startDate, "yyyy-MM-dd"),
            departureDate: format(date[0].endDate, "yyyy-MM-dd")
        };

        try {
            const response = await axios.post('/api/reserve', reservationData);
            if (response.status === 201) {
                alert('Reservation successful!');
                navigate('/confirmation', { state: { RoomType, date, searchPref, totalCost } });
            } else {
                alert('Failed to create reservation');
            }
        } catch (error) {
            alert('Error: ' + error.message);
        }
    };

    return (
        <div className="p-4 flex-col">
            <div className="container mx-auto p-8">
                <div className="max-w-md mx-auto bg-white border border-gray-200 rounded-lg shadow-lg">
                    <div className="p-6">
                        <h1 className="text-2xl font-bold mb-4">Booking Confirmation</h1>
                        <img src={selectedRoom.imageUrl} alt="Picture of Room" className="hover:scale-105"/>
                        <div className="mb-4">
                            <h2 className="text-xl font-semibold">Room Type</h2>
                            <p className="text-gray-600">{RoomType}</p>
                        </div>

                        <div className="mb-4">
                            <h2 className="text-xl font-semibold">Guests</h2>
                            <p className="text-gray-600">Adults: {searchPref.adult}</p>
                            <p className="text-gray-600">Children: {searchPref.children}</p>
                            <p className="text-gray-600">Total Rooms: {searchPref.room}</p>
                        </div>

                        <div className="mb-4">
                            <h2 className="text-xl font-semibold">Dates</h2>
                            <p className="text-gray-600">
                                {`${format(date[0].startDate, "MM/dd/yyyy")} to ${format(date[0].endDate, "MM/dd/yyyy")}`}
                            </p>
                        </div>

                        <div className="mb-4">
                            <h2 className="text-xl font-semibold">Total Cost</h2>
                            <p className="text-gray-600">$ {totalCost.toFixed(2)}</p>
                        </div>

                        <div className="mb-4">
                            <MDBInput label="Name" value={name} onChange={(e) => setName(e.target.value)} />
                        </div>

                        <div className="mb-4">
                            <MDBInput label="Phone Number" value={phone} onChange={(e) => setPhone(e.target.value)} />
                        </div>

                        <MDBBtn color="primary" onClick={handleConfirmBooking}>
                            Confirm Booking
                        </MDBBtn>
                    </div>
                </div>
            </div>
        </div>
    );
}
