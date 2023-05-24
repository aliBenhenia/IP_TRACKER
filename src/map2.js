import React, { useRef, useEffect } from 'react';
import { loadModules } from 'esri-loader';

const Map = ({ lat, lng }) => {
  const mapRef = useRef();

  useEffect(() => {
    loadModules(['esri/Map', 'esri/views/MapView'], { css: true }).then(([Map, MapView]) => {
      const map = new Map({
        basemap: 'streets-vector'
      });

      const view = new MapView({
        container: mapRef.current,
        map: map,
        center: [lng, lat],
        zoom: 12
      });
    });
  }, [lat, lng]);

  return <div className="map" ref={mapRef}></div>;
};

export default Map;
