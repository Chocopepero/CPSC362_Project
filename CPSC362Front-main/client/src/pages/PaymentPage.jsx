import { Link } from "react-router-dom"
import React, { useState } from 'react';

export default function PaymentPage() {
    const [cardType, setCardType] = useState('');
    const [cardNumber, setCardNumber] = useState('');
    const [expirationDate, setExpirationDate] = useState('');
    const [cvv, setCvv] = useState('');
    const [nameOnCard, setNameOnCard] = useState('');
    const [error, setError] = useState(null);
    const [success, setSuccess] = useState(false);

    function processPayment(ev) {
        ev.preventDefault();

        // Simulating a successful payment process
        const isPaymentSuccessful = true;

        if (isPaymentSuccessful) {
            setSuccess(true);
            setError(null);
        } else {
            setSuccess(false);
            setError('Payment failed. Please try again.');
        }
    }

    return (
        <div className="flex justify-center items-center h-screen bg-gray-100">
            <div className="w-full max-w-md bg-white p-8 rounded-lg shadow-lg">
                <h2 className="text-3xl font-bold mb-6 text-center text-black-600">Payment</h2>
                <form onSubmit={processPayment}>
                    <div className="mb-4">
                        <label className="block text-gray-700 font-medium">Card Type</label>
                        <select
                            value={cardType}
                            onChange={(e) => setCardType(e.target.value)}
                            required
                            className="w-full px-3 py-2 border rounded-lg focus:outline-none focus:ring-2 focus:ring-blue-600 transition duration-300"
                        >
                            <option value="" disabled>Select card type</option>
                            <option value="Visa">Visa</option>
                            <option value="MasterCard">MasterCard</option>
                        </select>
                    </div>
                    <div className="mb-4">
                        <label className="block text-gray-700 font-medium">Card Number</label>
                        <input
                            type="text"
                            value={cardNumber}
                            onChange={(e) => setCardNumber(e.target.value)}
                            required
                            className="w-full px-3 py-2 border rounded-lg focus:outline-none focus:ring-2 focus:ring-blue-600 transition duration-300"
                            placeholder="****-****-****-****"
                        />
                    </div>
                    <div className="mb-4">
                        <label className="block text-gray-700 font-medium">Expiration Date</label>
                        <input
                            type="text"
                            value={expirationDate}
                            onChange={(e) => setExpirationDate(e.target.value)}
                            required
                            className="w-full px-3 py-2 border rounded-lg focus:outline-none focus:ring-2 focus:ring-blue-600 transition duration-300"
                            placeholder="MM/YY"
                        />
                    </div>
                    <div className="mb-4">
                        <label className="block text-gray-700 font-medium">CVV</label>
                        <input
                            type="text"
                            value={cvv}
                            onChange={(e) => setCvv(e.target.value)}
                            required
                            className="w-full px-3 py-2 border rounded-lg focus:outline-none focus:ring-2 focus:ring-blue-600 transition duration-300"
                            placeholder="123"
                        />
                    </div>
                    <div className="mb-6">
                        <label className="block text-gray-700 font-medium">Name on Card</label>
                        <input
                            type="text"
                            value={nameOnCard}
                            onChange={(e) => setNameOnCard(e.target.value)}
                            required
                            className="w-full px-3 py-2 border rounded-lg focus:outline-none focus:ring-2 focus:ring-blue-600 transition duration-300"
                            placeholder="John Doe"
                        />
                    </div>
                    <button type="submit" className="w-full bg-blue-600 text-white py-2 rounded-lg hover:bg-blue-700 transition duration-300 font-semibold">
                        Make Payment
                    </button>
                </form>
                {error && <p className="mt-4 text-red-600">{error}</p>}
                {success && <p className="mt-4 text-green-600">Payment successful!</p>}
            </div>
        </div>
    );
}
