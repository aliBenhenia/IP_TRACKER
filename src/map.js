import React from "react";
import { MapContainer, TileLayer, Marker } from "react-leaflet";
import MarkerClusterGroup from "react-leaflet-markercluster";

// import "./";

const MyMaps = (props) => {
  return (
    <>
        <MapContainer
        className="markercluster-map"
        center={[props.lat, props.long]}
        zoom={10}
        maxZoom={18}
        >
        <TileLayer
            url="https://{s}.tile.openstreetmap.org/{z}/{x}/{y}.png"
            attribution='&copy; <a href="http://osm.org/copyright">OpenStreetMap</a> contributors'
        />

        {/* <MarkerClusterGroup> */}
            {/* <Marker position={[props.lat, props.long]} /> */}
        {/* </MarkerClusterGroup> */}
        </MapContainer>
    </>
  );
};

export default MyMaps;
