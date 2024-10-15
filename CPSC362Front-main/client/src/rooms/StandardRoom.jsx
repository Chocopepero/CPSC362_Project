import React, { useState, useRef, useEffect } from "react";
import { DateRange } from "react-date-range";
import { format } from "date-fns";
import "react-date-range/dist/styles.css"; // main css file
import "react-date-range/dist/theme/default.css"; // theme css file
import stdRoomImg1 from '../images/StandardRoom1.jpg'; 
import stdRoomImg2 from '../images/StandardRoom2.jpg'; 
import stdRoomImg3 from '../images/StandardRoom3.jpg';
import stdRoomImg4 from '../images/StandardRoom4.jpg';
import stdRoomImg5 from '../images/StandardRoom5.jpg';
import { FontAwesomeIcon } from '@fortawesome/react-fontawesome';
import { faBed, faWifi } from '@fortawesome/free-solid-svg-icons';
import { faCalendarXmark } from '@fortawesome/free-regular-svg-icons';
import { useNavigate } from "react-router-dom";
import { faCalendarDays, faPerson } from '@fortawesome/free-solid-svg-icons';

export default function StandardRoom() {
    const [openDate, setOpenDate] = useState(false);
    const [date, setDate] = useState([
        {
            startDate: new Date(),
            endDate: new Date(),
            key: "selection",
        },
    ]);
    const [openOptions, setOpenOptions] = useState(false);
    const [searchPref, setPreferenceSearch] = useState({
        adult: 1,
        children: 0,
        room: 1,
    });
    const [error, setError] = useState(null);

    const navigate = useNavigate();
    const dateRangeRef = useRef(null);
    const optionsRef = useRef(null);

    const handleOption = (name, operation) => {
        setPreferenceSearch((prev) => ({
            ...prev,
            [name]: operation === "i" ? prev[name] + 1 : prev[name] - 1,
        }));
    };

    const calculateTotalPrice = () => {
        const nights = (date[0].endDate - date[0].startDate) / (1000 * 60 * 60 * 24);
        const pricePerNight = 200;
        const totalPrice = nights * pricePerNight * searchPref.room;
        return totalPrice;
    };

    const validateInputs = () => {
        const nights = (date[0].endDate - date[0].startDate) / (1000 * 60 * 60 * 24);
        if (nights <= 0) {
            return "Please select at least one night.";
        }
        if (searchPref.adult < 1) {
            return "At least one adult must be selected.";
        }
        if (searchPref.children < 0) {
            return "Number of children cannot be negative.";
        }
        if (searchPref.room < 1) {
            return "At least one room must be selected.";
        }
        return null;
    };

    const handleSearch = () => {
        const validationError = validateInputs();
        if (validationError) {
            setError(validationError);
            return;
        }
        const totalPrice = calculateTotalPrice();
        navigate("/confirmation", { state: { RoomType: 'Standard Room', date, searchPref, totalPrice } });
    };

    const handleClickOutside = (event) => {
        if (dateRangeRef.current && !dateRangeRef.current.contains(event.target)) {
            setOpenDate(false);
        }
        if (optionsRef.current && !optionsRef.current.contains(event.target)) {
            setOpenOptions(false);
        }
    };

    useEffect(() => {
        document.addEventListener('mousedown', handleClickOutside);
        return () => {
            document.removeEventListener('mousedown', handleClickOutside);
        };
    }, []);

    return (
        <div className="max-w-6xl mx-auto p-6">
            <div className="bg-white shadow-lg rounded-lg p-6 flex">
                <div className="w-1/2 pr-4">
                    <div className="grid grid-cols-2 gap-4">
                        <img src={stdRoomImg1} alt="Standard Room" className="w-full h-32 object-cover rounded-lg" />
                        <img src={stdRoomImg2} alt="Standard Room" className="w-full h-32 object-cover rounded-lg" />
                        <img src={stdRoomImg3} alt="Standard Room" className="w-full h-32 object-cover rounded-lg" />
                        <img src={stdRoomImg4} alt="Standard Room" className="w-full h-32 object-cover rounded-lg" />
                        <img src={stdRoomImg5} alt="Standard Room" className="w-full h-32 object-cover rounded-lg" />
                    </div>
                </div>
                <div className="w-1/2 pl-4 flex flex-col justify-between">
                    <div>
                        <h2 className="text-2xl font-semibold mb-4 text-center">Standard Room</h2>
                        <p className="room-description text-gray-700 mb-4">A spacious room with a beautiful view of the city.</p>
                        <div className="flex items-start justify-start mb-4 flex-col space-y-4">
                            <div className="flex items-center">
                                <FontAwesomeIcon icon={faBed} className="h-6 w-6 text-gray-600" />
                                <span className="ml-2">3 Rooms</span>
                            </div>
                            <div className="flex items-center">
                                <FontAwesomeIcon icon={faWifi} className="h-6 w-6 text-gray-600" />
                                <span className="ml-2">Free WiFi</span>
                            </div>
                            <div className="flex items-center">
                                <FontAwesomeIcon icon={faCalendarXmark} className="h-6 w-6 text-gray-600" />
                                <span className="ml-2">Free cancellation two weeks prior</span>
                            </div>
                        </div>
                        <p className="room-price text-xl font-semibold text-blue-600 mb-5">$100 per night</p>
                    </div>
                    <div className="py-auto flex flex-col justify-stretch gap-10">
                        <div className="flex items-center gap-2">
                            <FontAwesomeIcon icon={faBed} className="text-lightgray" />
                            <span className="text-lightgray text-lg">Standard Room</span>
                        </div>
                        <div className="flex items-center gap-2 text-lg">
                            <FontAwesomeIcon icon={faCalendarDays} className="text-lightgray" />
                            <span
                                onClick={() => setOpenDate(!openDate)}
                                className="text-lightgray cursor-pointer"
                            >
                                {`${format(date[0].startDate, "MM/dd/yyyy")} to ${format(date[0].endDate, "MM/dd/yyyy")}`}
                            </span>
                            {openDate && (
                                <div ref={dateRangeRef} className="absolute ml-60 z-40">
                                    <DateRange
                                        editableDateInputs
                                        onChange={(item) => setDate([item.selection])}
                                        moveRangeOnFirstSelection={false}
                                        ranges={date}
                                        className="date"
                                        minDate={new Date()}
                                    />
                                </div>
                            )}
                        </div>
                        <div className="flex items-center gap-2 text-lg">
                            <FontAwesomeIcon icon={faPerson} className="text-lightgray" />
                            <span
                                onClick={() => setOpenOptions(!openOptions)}
                                className="text-lightgray cursor-pointer"
                            >
                                {`${searchPref.adult} adult · ${searchPref.children} children · ${searchPref.room} room`}
                            </span>
                            {openOptions && (
                                <div ref={optionsRef} className="absolute ml-60 z-40 bg-white text-gray rounded-5 shadow-lg">
                                    <div className="w-48 flex justify-between m-2">
                                        <span className="optionText">Adult</span>
                                        <div className="flex items-center gap-2 text-xs text-black">
                                            <button
                                                disabled={searchPref.adult <= 1}
                                                className="w-8 h-8 border border-solid border-blue-700 text-blue-700 shadow-lg rounded-b-md cursor-pointer bg-white"
                                                onClick={() => handleOption("adult", "d")}
                                            >
                                                -
                                            </button>
                                            <span className="optionCounterNumber">{searchPref.adult}</span>
                                            <button
                                                className="w-8 h-8 border border-solid border-blue-700 text-blue-700 shadow-lg rounded-t-md cursor-pointer bg-white"
                                                onClick={() => handleOption("adult", "i")}
                                            >
                                                +
                                            </button>
                                        </div>
                                    </div>
                                    <div className="w-48 flex justify-between m-2">
                                        <span className="optionText">Children</span>
                                        <div className="flex items-center gap-2 text-xs text-black">
                                            <button
                                                disabled={searchPref.children <= 0}
                                                className="w-8 h-8 border border-solid border-blue-700 text-blue-700 shadow-lg rounded-b-md cursor-pointer bg-white"
                                                onClick={() => handleOption("children", "d")}
                                            >
                                                -
                                            </button>
                                            <span className="optionCounterNumber">{searchPref.children}</span>
                                            <button
                                                className="w-8 h-8 border border-solid border-blue-700 text-blue-700 shadow-lg rounded-t-md cursor-pointer bg-white"
                                                onClick={() => handleOption("children", "i")}
                                            >
                                                +
                                            </button>
                                        </div>
                                    </div>
                                    <div className="w-48 flex justify-between m-2">
                                        <span className="optionText">Room</span>
                                        <div className="flex items-center gap-2 text-xs text-black">
                                            <button
                                                disabled={searchPref.room <= 1}
                                                className="w-8 h-8 border border-solid border-blue-700 text-blue-700 shadow-lg rounded-b-md cursor-pointer bg-white"
                                                onClick={() => handleOption("room", "d")}
                                            >
                                                -
                                            </button>
                                            <span className="optionCounterNumber">{searchPref.room}</span>
                                            <button
                                                className="w-8 h-8 border border-solid border-blue-700 text-blue-700 shadow-lg rounded-t-md cursor-pointer bg-white"
                                                onClick={() => handleOption("room", "i")}
                                            >
                                                +
                                            </button>
                                        </div>
                                    </div>
                                </div>
                            )}
                        </div>
                        {error && <div className="text-red-600">{error}</div>}
                        <div className="flex items-center gap-2 pr-2">
                            <button className="bg-blue-600 text-white py-2 px-5 border-white cursor-pointer rounded-full" onClick={handleSearch}>
                                Book Now
                            </button>
                        </div>
                    </div>
                </div>
            </div>
        </div>
    );
}
